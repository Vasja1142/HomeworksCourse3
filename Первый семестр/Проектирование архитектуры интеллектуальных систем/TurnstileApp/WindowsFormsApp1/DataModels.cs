// DataModels.cs
using System;

namespace TurnstileApp
{
    public class AccessCard
    {
        public string CardID { get; set; }
        public string EmployeeID { get; set; }
        public DateTime ExpirationDate { get; set; }
        public CardStatus Status { get; set; }

        // Для отображения в ComboBox
        public override string ToString()
        {
            return $"Карта {CardID} ({EmployeeID})";
        }
    }

    public class AccessLog
    {
        public string EmployeeID { get; set; }
        public DateTime Timestamp { get; set; }
        public AccessType AccessType { get; set; }
    }
}