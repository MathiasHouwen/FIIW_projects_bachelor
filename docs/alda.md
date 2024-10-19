# ALDA practicum 1

## gedeelde classes
- DateTime: d, m, y, hr, min
- TimeSpan: DateTime, duration
- Event: timeSpan, description
- Agenda: username, n*{event}

## PORGRAMMA 1
### DataStructuur:
### ALgoritmes:
### Interface:
- getEventsFromAgenda(agendaUserName) -> Agenda
- getEventsAtStartTime(Time) -> n*{agenda, Event}
- createNewAgenda(username) : void
- addEvent(agenda, event) : void
## PORGRAMMA 2
### DataStructuur:
### ALgoritmes:
### Interface:
- addEvent(agenda, event, attendees[]) : void
    - ⚠️people die op dat moment niet vrij zijn negeren

- updateEventName(event, name) : void
- __zelfde__Time(...) : void
- __zelfde__Duration(...) : void
- __zelfde__attendees(...) : void
    - ⚠️check voor overlaps

- getEventsFromAgenda(agendaUserName) -> Agenda met attendees

## PORGRAMMA 3
### DataStructuur:
### ALgoritmes:
### Interface:
- autoplan(event, attendees) (geen attendee negeren als 1 niet past. moeten allemaal passen) : void
- getEventsSorted(agendas[]) -> n*{event}