// ComponentClasses.cs
using System;
using System.Drawing;
using System.Windows.Forms;

namespace TurnstileApp
{
    // Интерфейсы для компонентов
    public interface IIndicator { void TurnOn(); void TurnOff(); }
    public interface IBuzzer { 
        void PlaySound(); 
    }
    public interface IPassageTimer { void Start(); void Stop(); }

    // Реализация Индикатора, управляющего элементом Panel на форме
    public class UiIndicator : IIndicator
    {
        private readonly Panel _panel;
        private readonly Color _onColor;
        private readonly Color _offColor = Color.Gray;

        public UiIndicator(Panel panel, Color onColor)
        {
            _panel = panel;
            _onColor = onColor;
            TurnOff(); // Начальное состояние
        }
        public void TurnOn() => _panel.BackColor = _onColor;
        public void TurnOff() => _panel.BackColor = _offColor;
    }

    // Реализация Звукового сигнала
    public class UiBuzzer : IBuzzer
    {
        public void PlaySound() => System.Media.SystemSounds.Hand.Play();
    }

    public interface ISensor
    {
        event Action<ISensor> MovementDetected;
        void SimulateDetection(); // Метод для симуляции срабатывания
        string SensorId { get; }
    }

    // Реализация Таймера прохода
    public class PassageTimer : IPassageTimer
    {
        private readonly Timer _timer;
        public PassageTimer(Timer timer)
        {
            _timer = timer;
        }
        public void Start() => _timer.Start();
        public void Stop() => _timer.Stop();
    }

    public class Sensor : ISensor
    {
        public event Action<ISensor> MovementDetected;
        public string SensorId { get; }

        public Sensor(string id)
        {
            SensorId = id;
        }

        // Этот метод будет вызываться из UI для имитации прохода
        public void SimulateDetection()
        {
            // Сообщаем всем подписчикам (нашему Турникету), что было движение
            MovementDetected?.Invoke(this);
        }
    }
}