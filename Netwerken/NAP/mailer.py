import smtplib
from email.mime.text import MIMEText

import config

EMAIL = config.EMAIL
PASSWORD = config.EMAIL_PASSWORD
SMTP_SERVER = "smtp.gmail.com"
SMTP_PORT = 587

def send_email(to, subject, body):
    msg = MIMEText(body)
    msg["Subject"] = subject
    msg["From"] = EMAIL
    msg["To"] = to

    try:
        with smtplib.SMTP(SMTP_SERVER, SMTP_PORT) as server:
            server.starttls()
            server.login(EMAIL, PASSWORD)
            server.send_message(msg)
        print(f"[MAIL] Verzonden naar {to}")
    except Exception as e:
        print(f"[FOUT] Mailen naar {to} mislukt: {e}")

def send_invitation(email, poll_id, event_name):
    link = f"http://localhost:5000/poll/{poll_id}"
    body = f"Je bent uitgenodigd om te stemmen voor '{event_name}'. Ga naar: {link}"
    send_email(email, f"Uitnodiging voor {event_name}", body)


def send_update_to_organizer(email, voter):
    body = f"{voter} heeft gestemd. Bekijk de poll: http://localhost:5000/poll"
    send_email(email, "Nieuwe stem ontvangen", body)

def send_final_date_to_all(emails, final_date):
    for email in emails:
        body = f"De definitieve datum is vastgelegd: {final_date}"
        send_email(email, "Definitieve datum gekozen", body)
