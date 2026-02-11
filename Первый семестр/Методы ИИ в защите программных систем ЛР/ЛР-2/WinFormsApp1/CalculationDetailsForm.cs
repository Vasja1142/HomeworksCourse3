using System;
using System.Collections.Generic;
using System.Text;
using System.Windows.Forms;

namespace RSAEncryption
{
    public partial class CalculationDetailsForm : Form
    {
        public CalculationDetailsForm(long p, long q, long n, long phi, long e, long d, string originalText, List<long> encryptedData)
        {
            InitializeComponent();
            PopulateDetails(p, q, n, phi, e, d, originalText, encryptedData);
        }

        private void PopulateDetails(long p, long q, long n, long phi, long e, long d, string originalText, List<long> encryptedData)
        {
            // --- Генерация ключей ---
            var sbKeys = new StringBuilder();
            sbKeys.AppendLine("1. Выбираются два случайных простых числа p и q (разрядностью не менее 12 бит):");
            sbKeys.AppendLine($"   p = {p}");
            sbKeys.AppendLine($"   q = {q}");
            sbKeys.AppendLine();
            sbKeys.AppendLine("2. Вычисляется модуль n (часть открытого ключа):");
            sbKeys.AppendLine($"   n = p * q = {p} * {q} = {n}");
            sbKeys.AppendLine();
            sbKeys.AppendLine("3. Вычисляется функция Эйлера φ(n):");
            sbKeys.AppendLine($"   φ(n) = (p - 1) * (q - 1) = {p - 1} * {q - 1} = {phi}");
            sbKeys.AppendLine();
            sbKeys.AppendLine("4. Выбирается открытая экспонента e:");
            sbKeys.AppendLine($"   Выбрано e = {e}. Число e должно быть взаимно простым с φ(n), то есть НОД(e, φ(n)) = 1.");
            sbKeys.AppendLine();
            sbKeys.AppendLine("5. Вычисляется секретная экспонента d (часть закрытого ключа):");
            sbKeys.AppendLine($"   d подбирается так, чтобы выполнялось условие (e * d) mod φ(n) = 1.");
            sbKeys.AppendLine($"   d = {d} (найдено с помощью расширенного алгоритма Евклида).");
            sbKeys.AppendLine();
            sbKeys.AppendLine("РЕЗУЛЬТАТ:");
            sbKeys.AppendLine($"   Открытый ключ: (e={e}, n={n})");
            sbKeys.AppendLine($"   Закрытый ключ: (d={d}, n={n})");

            rtbKeyGeneration.Text = sbKeys.ToString();

            // --- Шифрование ---
            if (!string.IsNullOrEmpty(originalText) && encryptedData != null && encryptedData.Count > 0)
            {
                char charToEncrypt = originalText[0];
                long m = charToEncrypt;
                long c = encryptedData[0];

                var sbEncrypt = new StringBuilder();
                sbEncrypt.AppendLine($"Возьмем для примера первый символ исходного текста: '{charToEncrypt}'");
                sbEncrypt.AppendLine($"Его ASCII-код (сообщение M): {m}");
                sbEncrypt.AppendLine();
                sbEncrypt.AppendLine("Формула шифрования: C = M^e mod n");
                sbEncrypt.AppendLine($"C = {m}^{e} mod {n}");
                sbEncrypt.AppendLine($"Результат вычисления (шифротекст C): {c}");

                rtbEncryption.Text = sbEncrypt.ToString();

                // --- Дешифрование ---
                var sbDecrypt = new StringBuilder();
                sbDecrypt.AppendLine($"Возьмем первое число из зашифрованного текста: {c}");
                sbDecrypt.AppendLine();
                sbDecrypt.AppendLine("Формула дешифрования: M = C^d mod n");
                sbDecrypt.AppendLine($"M = {c}^{d} mod {n}");
                sbDecrypt.AppendLine($"Результат вычисления (ASCII-код): {m}");
                sbDecrypt.AppendLine();
                sbDecrypt.AppendLine($"Полученный код {m} соответствует исходному символу '{charToEncrypt}'.");

                rtbDecryption.Text = sbDecrypt.ToString();
            }
            else
            {
                rtbEncryption.Text = "Сначала выполните шифрование на главной форме.";
                rtbDecryption.Text = "Сначала выполните шифрование на главной форме.";
            }
        }
    }
}