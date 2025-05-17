import uuid
import json

STORAGE_FILE = "storage.json"

def load_storage():
    try:
        with open(STORAGE_FILE, "r") as f:
            return json.load(f)
    except FileNotFoundError:
        return {}

def save_storage(data):
    with open(STORAGE_FILE, "w") as f:
        json.dump(data, f, indent=4)

def create_poll(organizer_email, dates):
    poll_id = str(uuid.uuid4())
    data = load_storage()
    data[poll_id] = {
        "organizer": organizer_email,
        "dates": {date: [] for date in dates},
        "voted": [],
        "final_date": None
    }
    save_storage(data)
    return poll_id

def vote(poll_id, user_email, selected_dates):
    data = load_storage()
    if poll_id not in data or user_email in data[poll_id]["voted"]:
        return False

    for date in selected_dates:
        if date in data[poll_id]["dates"]:
            data[poll_id]["dates"][date].append(user_email)

    data[poll_id]["voted"].append(user_email)
    save_storage(data)
    return True

def get_poll(poll_id):
    data = load_storage()
    return data.get(poll_id)

def finalize_poll(poll_id):
    data = load_storage()
    poll = data.get(poll_id)
    if not poll:
        return None

    max_votes = 0
    final_date = None
    for date, voters in poll["dates"].items():
        if len(voters) > max_votes:
            max_votes = len(voters)
            final_date = date

    poll["final_date"] = final_date
    save_storage(data)
    return final_date
