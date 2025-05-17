def send_invitation(email, poll_id):
    print(f"[MAIL] Naar {email}: Je bent uitgenodigd voor poll {poll_id}")

def send_update_to_organizer(email, voter):
    print(f"[MAIL] Naar {email}: {voter} heeft gestemd.")

def send_final_date_to_all(emails, final_date):
    for email in emails:
        print(f"[MAIL] Naar {email}: De definitieve datum is {final_date}")
