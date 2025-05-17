from flask import Flask, request, jsonify, render_template
from poll import create_poll, vote, get_poll, finalize_poll
from mailer import send_invitation, send_update_to_organizer, send_final_date_to_all
from weather_api import get_weather_for_date

app = Flask(__name__)

@app.route("/create_poll", methods=["POST"])
def create():
    data = request.json
    poll_id = create_poll(data["organizer_email"], data["dates"])
    for email in data["invitees"]:
        send_invitation(email, poll_id)
    return jsonify({"poll_id": poll_id})

@app.route("/vote", methods=["POST"])
def vote_endpoint():
    data = request.json
    success = vote(data["poll_id"], data["user_email"], data["dates"])
    if not success:
        return jsonify({"error": "Stemmen mislukt"}), 400
    poll = get_poll(data["poll_id"])
    send_update_to_organizer(poll["organizer"], data["user_email"])
    return jsonify({"status": "Succesvol gestemd"})

@app.route("/poll/<poll_id>", methods=["GET"])
def get_poll_info(poll_id):
    poll = get_poll(poll_id)
    if not poll:
        return jsonify({"error": "Poll niet gevonden"}), 404
    weather = {date: get_weather_for_date(date) for date in poll["dates"]}
    return jsonify({"poll": poll, "weather": weather})

@app.route("/finalize_poll", methods=["POST"])
def finalize():
    data = request.json
    final_date = finalize_poll(data["poll_id"])
    if not final_date:
        return jsonify({"error": "Poll niet gevonden"}), 404
    poll = get_poll(data["poll_id"])
    all_voters = list(set(voter for voters in poll["dates"].values() for voter in voters))
    send_final_date_to_all([poll["organizer"]] + all_voters, final_date)
    return jsonify({"final_date": final_date})

@app.route("/")
def index():
    return render_template("index.html")


if __name__ == "__main__":
    app.run(debug=True)
