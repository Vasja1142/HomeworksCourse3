// Enums.cs
namespace TurnstileApp
{
    // Состояния турникета из диаграммы классов
    public enum TurnstileState
    {
        LOCKED,
        AWAITING_PASSAGE
    }

    // Статусы карт из диаграммы классов
    public enum CardStatus
    {
        ACTIVE,
        EXPIRED,
        BLOCKED
    }

    // Типы прохода из диаграммы классов
    public enum AccessType
    {
        ENTRY,
        EXIT
    }
}