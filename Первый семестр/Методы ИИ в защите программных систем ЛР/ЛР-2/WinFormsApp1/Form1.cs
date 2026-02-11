using System;
using System.Collections.Generic;
using System.Windows.Forms;

namespace RSAEncryption
{
    public partial class Form1 : Form
    {
        private SimpleRSA rsa;
        private List<long> lastEncryptedData;

        public Form1()
        {
            InitializeComponent();
            rsa = new SimpleRSA();
        }

        private void btnGenerateKeys_Click(object sender, EventArgs e)
        {
            try
            {
                rsa.GenerateKeys();
                var publicKey = rsa.GetPublicKey();
                var privateKey = rsa.GetPrivateKey();

                txtPublicKey.Text = $"(e = {publicKey.Item1}, n = {publicKey.Item2})";
                txtPrivateKey.Text = $"(d = {privateKey.Item1}, n = {privateKey.Item2})";

                btnEncrypt.Enabled = true;
                btnDecrypt.Enabled = true; 
                btnShowDetails.Enabled = false;

                MessageBox.Show("Ключи сгенерированы успешно!", "Информация",
                               MessageBoxButtons.OK, MessageBoxIcon.Information);
            }
            catch (Exception ex)
            {
                MessageBox.Show($"Ошибка при генерации ключей: {ex.Message}", "Ошибка",
                               MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }

        private void btnEncrypt_Click(object sender, EventArgs e)
        {
            if (string.IsNullOrEmpty(txtInput.Text))
            {
                MessageBox.Show("Введите текст для шифрования!", "Ошибка", MessageBoxButtons.OK, MessageBoxIcon.Error);
                return;
            }

            try
            {
                var encrypted = rsa.EncryptString(txtInput.Text);
                this.lastEncryptedData = encrypted;

                string encryptedText = "[" + string.Join(", ", encrypted) + "]";


                txtEncrypted.Text = encryptedText;

                btnShowDetails.Enabled = true;
            }
            catch (Exception ex)
            {
                MessageBox.Show($"Ошибка при шифровании: {ex.Message}", "Ошибка", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }


        private void btnDecrypt_Click(object sender, EventArgs e)
        {
            if (string.IsNullOrEmpty(txtEncrypted.Text))
            {
                MessageBox.Show("Введите зашифрованный текст для дешифрования!", "Ошибка",
                               MessageBoxButtons.OK, MessageBoxIcon.Error);
                return;
            }

            try
            {
                // Парсим зашифрованный текст обратно в список чисел
                var cleanText = txtEncrypted.Text.Trim('[', ']', ' ');
                var numbers = cleanText.Split(new[] { ',' }, StringSplitOptions.RemoveEmptyEntries);

                var encryptedList = new List<long>();
                foreach (var num in numbers)
                {
                    if (long.TryParse(num.Trim(), out long value))
                    {
                        encryptedList.Add(value);
                    }
                    else
                    {
                        throw new ArgumentException($"Неверный формат числа: {num}");
                    }
                }

                var decrypted = rsa.DecryptString(encryptedList);
                txtDecrypted.Text = decrypted;

                // Упрощенная проверка результата
                if (!string.IsNullOrEmpty(txtInput.Text))
                {
                    if (txtInput.Text == decrypted)
                    {
                        MessageBox.Show("✓ Дешифрование прошло успешно! Исходный текст совпадает.", "Проверка",
                                       MessageBoxButtons.OK, MessageBoxIcon.Information);
                    }
                    else
                    {
                        MessageBox.Show("✗ Внимание! Дешифрованный текст не совпадает с исходным.", "Ошибка",
                                       MessageBoxButtons.OK, MessageBoxIcon.Error);
                    }
                }
                else
                {
                    MessageBox.Show("Текст успешно дешифрован!", "Информация",
                                    MessageBoxButtons.OK, MessageBoxIcon.Information);
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show($"Ошибка при дешифровании: {ex.Message}", "Ошибка",
                               MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }

        private void btnShowDetails_Click(object sender, EventArgs e)
        {
            if (rsa == null || lastEncryptedData == null)
            {
                MessageBox.Show("Сначала необходимо сгенерировать ключи и зашифровать текст.", "Информация", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                return;
            }

            var detailsForm = new CalculationDetailsForm(
                rsa.P, rsa.Q, rsa.N, rsa.Phi, rsa.E, rsa.D,
                txtInput.Text,
                lastEncryptedData
            );
            detailsForm.ShowDialog();
        }
    }

    public class SimpleRSA
    {
        // Приватные поля для хранения ключей
        private long p, q, n, phi, e, d;
        private Random random = new Random();

        // Публичные свойства для доступа к значениям (для окна расчетов)
        public long P => p;
        public long Q => q;
        public long N => n;
        public long Phi => phi;
        public long E => e;
        public long D => d;


        // Является ли число простым
        private bool IsPrime(long n)
        {
            if (n <= 1) return false;
            if (n <= 3) return true;
            if (n % 2 == 0 || n % 3 == 0) return false;
            for (long i = 5; i * i <= n; i += 6)
            {
                if (n % i == 0 || n % (i + 2) == 0) return false;
            }
            return true;
        }

        // Генерация простого числа в заданном диапазоне
        private long GeneratePrime(long minVal, long maxVal)
        {
            long num;
            do { num = random.Next((int)minVal, (int)maxVal); if (num % 2 == 0) num++; }
            while (!IsPrime(num));
            return num;
        }

        // Наибольший общий делитель
        private long Gcd(long a, long b)
        {
            while (b != 0) { long temp = b; b = a % b; a = temp; }
            return a;
        }

        // Расширенный алгоритм Евклида для нахождения d
        private long ModInverse(long e_val, long phi_val)
        {
            long t = 0, new_t = 1;
            long r = phi_val, new_r = e_val;
            while (new_r != 0)
            {
                long quotient = r / new_r;
                (t, new_t) = (new_t, t - quotient * new_t);
                (r, new_r) = (new_r, r - quotient * new_r);
            }
            if (r > 1) return -1;
            if (t < 0) t += phi_val;
            return t;
        }

        // Возведение в степень по модулю
        private long ModPow(long baseValue, long exponent, long mod)
        {
            long result = 1;
            baseValue %= mod;
            while (exponent > 0)
            {
                if (exponent % 2 == 1) result = (result * baseValue) % mod;
                exponent >>= 1;
                baseValue = (baseValue * baseValue) % mod;
            }
            return result;
        }

        // Генерация ключей
        public void GenerateKeys()
        {
            p = GeneratePrime(2048, 4095);
            q = GeneratePrime(2048, 4095);
            while (p == q) { q = GeneratePrime(2048, 4095); }
            n = p * q;
            phi = (p - 1) * (q - 1);
            e = 65537;
            if (e >= phi || Gcd(e, phi) != 1) { e = 17; }
            if (e >= phi || Gcd(e, phi) != 1) { e = 3; }
            d = ModInverse(e, phi);
            if (d == -1) { throw new Exception("Не удалось найти обратный элемент для e"); }
        }

        // Шифрование строки
        public List<long> EncryptString(string text)
        {
            var encrypted = new List<long>();
            foreach (char c in text) { encrypted.Add(ModPow(c, e, n)); }
            return encrypted;
        }

        // Дешифрование в строку
        public string DecryptString(List<long> encrypted)
        {
            string decrypted = "";
            foreach (long c_val in encrypted) { decrypted += (char)ModPow(c_val, d, n); }
            return decrypted;
        }

        // Методы для получения ключей 
        public Tuple<long, long> GetPublicKey() => Tuple.Create(e, n);
        public Tuple<long, long> GetPrivateKey() => Tuple.Create(d, n);
    }
}
