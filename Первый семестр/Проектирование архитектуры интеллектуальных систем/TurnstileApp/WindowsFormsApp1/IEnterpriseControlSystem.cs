// IEnterpriseControlSystem.cs
using System.Collections.Generic;
using System.Linq;

namespace TurnstileApp
{
    // Интерфейс, как на диаграмме классов
    public interface IEnterpriseControlSystem
    {
        bool CheckIfEntryWasLogged(string employeeID);
        void SaveAccessLog(AccessLog log);
    }

    // Класс-симулятор для АСУ. Хранит данные в простом списке.
    public class MockEnterpriseControlSystem : IEnterpriseControlSystem
    {
        private readonly List<AccessLog> _logs = new List<AccessLog>();

        public bool CheckIfEntryWasLogged(string employeeID)
        {
            // Проверяем, есть ли запись о ВХОДЕ для этого работника,
            // для которой еще нет соответствующей записи о ВЫХОДЕ.
            var lastEntry = _logs
                .Where(log => log.EmployeeID == employeeID && log.AccessType == AccessType.ENTRY)
                .OrderByDescending(log => log.Timestamp)
                .FirstOrDefault();

            if (lastEntry == null) return false; // Никогда не входил

            var lastExit = _logs
                .Where(log => log.EmployeeID == employeeID && log.AccessType == AccessType.EXIT)
                .OrderByDescending(log => log.Timestamp)
                .FirstOrDefault();

            // Если последняя запись о выходе была раньше последней записи о входе, значит он внутри.
            return lastExit == null || lastExit.Timestamp < lastEntry.Timestamp;
        }

        public void SaveAccessLog(AccessLog log)
        {
            _logs.Add(log);
        }
    }
}