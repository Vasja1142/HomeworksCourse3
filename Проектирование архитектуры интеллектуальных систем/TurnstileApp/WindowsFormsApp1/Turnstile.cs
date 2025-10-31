// Turnstile.cs
using System;
using System.Collections.Generic;

namespace TurnstileApp
{
    public class Turnstile
    {
        // Поля для хранения объектов-компонентов, как на диаграмме
        private readonly IIndicator _goIndicator;
        private readonly IIndicator _stopIndicator;
        private readonly IBuzzer _buzzer;
        private readonly IPassageTimer _passageTimer;
        private readonly IEnumerable<ISensor> _sensors; // Коллекция датчиков

        private TurnstileState _state;
        private readonly bool _isForExit;
        private readonly IEnterpriseControlSystem _asu;

        /// <summary>
        /// Конструктор класса Турникет.
        /// </summary>
        /// <param name="isForExit">True, если турникет работает на выход.</param>
        /// <param name="asu">Реализация системы АСУ.</param>
        /// <param name="goIndicator">Индикатор "Проход".</param>
        /// <param name="stopIndicator">Индикатор "Стоп".</param>
        /// <param name="buzzer">Звуковой сигнализатор.</param>
        /// <param name="passageTimer">Таймер времени прохода.</param>
        /// <param name="sensors">Коллекция из трех датчиков прохода.</param>
        public Turnstile(bool isForExit, IEnterpriseControlSystem asu, IIndicator goIndicator, IIndicator stopIndicator, IBuzzer buzzer, IPassageTimer passageTimer, IEnumerable<ISensor> sensors)
        {
            _isForExit = isForExit;
            _asu = asu;
            _goIndicator = goIndicator;
            _stopIndicator = stopIndicator;
            _buzzer = buzzer;
            _passageTimer = passageTimer;
            _sensors = sensors;

            ResetToInitialState();
        }

        /// <summary>
        /// Обрабатывает сигнал от любого из датчиков.
        /// </summary>
        private void OnSensorMovementDetected(ISensor triggeredSensor)
        {
            // Реакция на несанкционированный проход (турникет заблокирован)
            if (_state == TurnstileState.LOCKED)
            {
                _buzzer.PlaySound();
            }
            // Реакция на санкционированный проход
            // ВАЖНО: Реагируем только на ПЕРВЫЙ сигнал, как в ТЗ
            else if (_state == TurnstileState.AWAITING_PASSAGE)
            {
                // Немедленно отписываемся от событий всех датчиков, чтобы игнорировать последующие сигналы
                UnsubscribeFromSensors();
                _passageTimer.Start();
            }
        }

        /// <summary>
        /// Основной метод, инициирующий проверку карты.
        /// </summary>
        public void InsertCard(AccessCard card)
        {
            if (_state != TurnstileState.LOCKED) return;

            if (!ValidateCard(card))
            {
                DenyAccessAndRetainCard();
                return;
            }

            if (_isForExit && !RequestEntryConfirmation(card.EmployeeID))
            {
                DenyAccessAndRetainCard();
                return;
            }

            GrantAccess(card.EmployeeID);
        }

        /// <summary>
        /// Сбрасывает турникет в начальное заблокированное состояние.
        /// </summary>
        public void ResetToInitialState()
        {
            _state = TurnstileState.LOCKED;
            _passageTimer.Stop();
            _stopIndicator.TurnOn();
            _goIndicator.TurnOff();

            // При сбросе нужно снова подписаться на события датчиков для следующего цикла
            SubscribeToSensors();
        }

        private void SubscribeToSensors()
        {
            foreach (var sensor in _sensors)
            {
                // Сначала отписываемся, чтобы избежать двойной подписки при повторном вызове
                sensor.MovementDetected -= OnSensorMovementDetected;
                sensor.MovementDetected += OnSensorMovementDetected;
            }
        }

        private void UnsubscribeFromSensors()
        {
            foreach (var sensor in _sensors)
            {
                sensor.MovementDetected -= OnSensorMovementDetected;
            }
        }

        private bool ValidateCard(AccessCard card)
        {
            return card.Status == CardStatus.ACTIVE && card.ExpirationDate >= DateTime.Now;
        }

        private bool RequestEntryConfirmation(string employeeID)
        {
            return _asu.CheckIfEntryWasLogged(employeeID);
        }

        private void GrantAccess(string employeeID)
        {
            _state = TurnstileState.AWAITING_PASSAGE;
            LogAccess(employeeID);

            _goIndicator.TurnOn();
            _stopIndicator.TurnOff();
        }

        private void DenyAccessAndRetainCard()
        {
            System.Media.SystemSounds.Exclamation.Play();
        }

        private void LogAccess(string employeeID)
        {
            var log = new AccessLog
            {
                EmployeeID = employeeID,
                Timestamp = DateTime.Now,
                AccessType = _isForExit ? AccessType.EXIT : AccessType.ENTRY
            };
            _asu.SaveAccessLog(log);
        }
    }
}