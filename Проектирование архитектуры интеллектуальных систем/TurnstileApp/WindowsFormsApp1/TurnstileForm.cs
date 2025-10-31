// TurnstileForm.cs (Form1.cs)
using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Windows.Forms;

namespace TurnstileApp
{
    public partial class TurnstileForm : Form
    {
        private Turnstile _turnstile;
        private readonly IEnterpriseControlSystem _asu = new MockEnterpriseControlSystem();
        private readonly List<AccessCard> _cards = new List<AccessCard>();
        private readonly List<Sensor> _sensors = new List<Sensor>(); // Список для хранения наших датчиков
        private readonly Random _random = new Random(); // Для случайного выбора датчика

        public TurnstileForm()
        {
            InitializeComponent();
            SetupApplication();
        }

        private void SetupApplication()
        {
            // Создаем три датчика один раз при запуске
            _sensors.Add(new Sensor("Датчик-1 (ближний)"));
            _sensors.Add(new Sensor("Датчик-2 (центральный)"));
            _sensors.Add(new Sensor("Датчик-3 (дальний)"));

            CreateTestData();
            cmbCards.DataSource = _cards;
            cmbCards.DisplayMember = "CardID";

            // Связываем таймер формы с нашей оберткой
            passageTimer.Tick += PassageTimer_Tick;

            CreateNewTurnstileInstance();

            clockTimer.Tick += ClockTimer_Tick;
            clockTimer.Start();
        }

        private void CreateNewTurnstileInstance()
        {
            // 1. Создаем объекты-компоненты, связывая их с элементами UI
            var goIndicator = new UiIndicator(panelGo, Color.LimeGreen);
            var stopIndicator = new UiIndicator(panelStop, Color.Red);
            var buzzer = new UiBuzzer();
            var timer = new PassageTimer(passageTimer);

            // 2. Создаем экземпляр турникета, ПЕРЕДАВАЯ ему его компоненты, включая датчики
            _turnstile = new Turnstile(rbExit.Checked, _asu, goIndicator, stopIndicator, buzzer, timer, _sensors);

            // 3. Обновляем UI и лог
            btnInsertCard.Enabled = true;
            btnWalkThrough.Enabled = true;
            Log("Система готова. Турникет настроен на " + (rbExit.Checked ? "ВЫХОД" : "ВХОД"));
        }

        private void btnInsertCard_Click(object sender, EventArgs e)
        {
            var selectedCard = cmbCards.SelectedItem as AccessCard;
            if (selectedCard != null)
            {
                Log($"Работник {selectedCard.EmployeeID} вставляет карту {selectedCard.CardID}.");
                _turnstile.InsertCard(selectedCard);

                // UI теперь нужно обновлять вручную после действий
                if (panelGo.BackColor == Color.LimeGreen)
                {
                    Log($"Доступ разрешен для {selectedCard.EmployeeID}. Карта возвращена.", Color.Green);
                    btnInsertCard.Enabled = false;
                }
                else
                {
                    Log($"Доступ запрещен. Карта {selectedCard.CardID} изъята.", Color.OrangeRed);
                }
            }
        }

        private void btnWalkThrough_Click(object sender, EventArgs e)
        {
            // Выбираем случайный датчик из трех
            int randomIndex = _random.Next(_sensors.Count);
            Sensor triggeredSensor = _sensors[randomIndex];

            Log($"Имитация прохода... Сработал '{triggeredSensor.SensorId}'");

            // Если проход не разрешен, сработает зуммер
            if (panelGo.BackColor != Color.LimeGreen)
            {
                Log("ТРЕВОГА! Попытка несанкционированного прохода!", Color.Red);
            }
            else // Если проход разрешен, запустится таймер
            {
                Log("Обнаружен санкционированный проход. Запущен таймер на 5 секунд.");
                btnWalkThrough.Enabled = false;
            }

            // Имитируем срабатывание выбранного датчика.
            // Турникет (который подписан на событие) отреагирует на это.
            triggeredSensor.SimulateDetection();
        }

        private void rbType_CheckedChanged(object sender, EventArgs e)
        {
            var changedRadioButton = sender as RadioButton;
            if (changedRadioButton == null || !changedRadioButton.Checked) return;

            if (_turnstile != null) CreateNewTurnstileInstance();
        }

        private void PassageTimer_Tick(object sender, EventArgs e)
        {
            // Таймер сработал, сбрасываем турникет в исходное состояние
            _turnstile.ResetToInitialState();
            btnInsertCard.Enabled = true;
            btnWalkThrough.Enabled = true;
            Log("Таймер истек. Турникет вернулся в исходное состояние.");
        }

        private void ClockTimer_Tick(object sender, EventArgs e)
        {
            lblClock.Text = DateTime.Now.ToString("HH:mm:ss");
        }

        private void Log(string message, Color? color = null)
        {
            // В WinForms для простоты цвет не используется, но параметр оставлен для гибкости
            string logEntry = $"{DateTime.Now:HH:mm:ss} - {message}";
            lbLog.Items.Insert(0, logEntry);
        }

        private void CreateTestData()
        {
            _cards.Add(new AccessCard { CardID = "C001", EmployeeID = "E-101", Status = CardStatus.ACTIVE, ExpirationDate = DateTime.Now.AddYears(1) });
            _cards.Add(new AccessCard { CardID = "C002", EmployeeID = "E-102", Status = CardStatus.ACTIVE, ExpirationDate = DateTime.Now.AddYears(1) });
            _cards.Add(new AccessCard { CardID = "C003", EmployeeID = "E-103", Status = CardStatus.ACTIVE, ExpirationDate = DateTime.Now.AddDays(-10) }); // Просроченная
            _cards.Add(new AccessCard { CardID = "C004", EmployeeID = "E-104", Status = CardStatus.BLOCKED, ExpirationDate = DateTime.Now.AddYears(1) }); // Заблокированная
        }
    }
}