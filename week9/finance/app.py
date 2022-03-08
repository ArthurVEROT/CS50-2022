import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd, f_buy

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/", methods=["GET", "POST"])
@login_required
def index():
    if request.method == "POST":
        dict_cash = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])
        cash = dict_cash[0]["cash"]

        results = f_buy(request.form.get("symbol"), request.form.get("num_share"), cash)

        db.execute("UPDATE users SET cash = ? WHERE id = ?", results["new_cash"], session["user_id"])
        db.execute("INSERT INTO transactions (id_buyer, symbol, shares, price, datetime) VALUES(?, ?, ?, ?, CURRENT_TIMESTAMP)",
                   session["user_id"], request.form.get("symbol"), request.form.get("num_share"), results["price"])

        return redirect("/")

    #"""Show portfolio of stocks"""
    else:
        symbols = db.execute(
            "SELECT symbol, SUM(shares) AS shares FROM transactions WHERE id_buyer = ? GROUP BY symbol HAVING SUM(shares) > 0", session["user_id"])

        index = len(symbols)
        total_assets = 0
        for i in range(index):
            quote = lookup(symbols[i]["symbol"])

            symbols[i]["name"] = quote["name"]
            symbols[i]["price"] = quote["price"]
            symbols[i]["total"] = symbols[i]["shares"] * quote["price"]
            total_assets += symbols[i]["total"]

        cash = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])
        total_assets += cash[0]["cash"]

        return render_template("index.html", symbols=symbols, cash=cash, total_assets=total_assets)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":
        # check for symbol
        if not request.form.get("symbol"):
            return apology("missing symbol")
        # check for shares
        elif not request.form.get("shares"):
            return apology("missing shares")
        # check for symbol in API
        elif lookup(request.form.get("symbol")) == None:
            return apology("invalid symbol")
        # check for positive integer shares
        else:
            try:
                if int(request.form.get("shares")) < 0:
                    return apology("Enter a positive number of shares")
            except ValueError:
                return apology("Enter a positive number of shares")

        # look for symbol
        quote = lookup(request.form.get("symbol"))
        cash = db.execute("SELECT * FROM users WHERE id = ?", session["user_id"])
        price = quote["price"]
        shares = float(request.form.get("shares"))

        if cash[0]["cash"] > (price * shares):
            new_cash = cash[0]["cash"] - (price * shares)
            db.execute("UPDATE users SET cash = ? WHERE id = ?", new_cash, session["user_id"])
            db.execute("INSERT INTO transactions (id_buyer, symbol, shares, price, datetime) VALUES(?, ?, ?, ?, CURRENT_TIMESTAMP)",
                        session["user_id"], quote["symbol"], request.form.get("shares"), price)

            # Redirect user to home page
            return redirect("/")

        else:
            return apology("can't afford")

    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    historic = db.execute("SELECT symbol, shares, price, datetime FROM transactions WHERE id_buyer = ?", session["user_id"])
    return render_template("history.html", historic=historic)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?",
                          request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == "POST":
        if not request.form.get("symbol"):
            return apology("type a symbol")
        elif lookup(request.form.get("symbol")) == None:
            return apology("invalid symbol")
        else:
            quote = lookup(request.form.get("symbol"))
            return render_template("quoted.html", quote=quote)
    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 400)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 400)

        # Ensure confirmation was submitted
        elif not request.form.get("confirmation"):
            return apology("please confirm your password", 400)

        # Ensure valid password
        elif request.form.get("password") != request.form.get("confirmation"):
            return apology("different password", 400)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username does not exist
        if len(rows) == 1:
            return apology("username already used", 400)
            # return render_template("register.html", alert=len(rows))

        db.execute("INSERT INTO users (username, hash) VALUES(?, ?)", request.form.get(
            "username"), generate_password_hash(request.form.get("password")))

        # Remember which user has logged in
        user_id = db.execute(
            "SELECT * FROM users WHERE username = ?", request.form.get("username"))
        session["user_id"] = user_id[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    # list of stock owned
    all_stocks = db.execute(
        "SELECT symbol, SUM(shares) AS shares FROM transactions WHERE id_buyer = ? GROUP BY symbol HAVING SUM(shares) > 0", session["user_id"])

    if request.method == "POST":
        # Checks
        if not request.form.get("symbol"):
            return apology("please select a symbol")
        if not request.form.get("shares"):
            return apology("missing shares")
        if int(request.form.get("shares")) < 0:
            return apology("Enter a positive integer number of shares")

        my_shares = db.execute("SELECT SUM(shares) AS shares FROM transactions WHERE id_buyer = ? AND symbol = ? GROUP BY symbol",
                               session["user_id"], request.form.get("symbol"))

        if not my_shares:
            return apology("you don't own any of these stock")

        if int(request.form.get("shares")) > int(my_shares[0]["shares"]):
            return apology("You do not own that many shares of the stock")

        # The sell
        # Update users db : cash
        quote = lookup(request.form.get("symbol"))
        cash = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])
        new_cash = cash[0]["cash"] + (quote["price"] * float(request.form.get("shares")))
        db.execute("UPDATE users SET cash = ? WHERE id = ?", new_cash, session["user_id"])

        # Update transaction db
        db.execute("INSERT INTO transactions (id_buyer, symbol, shares, price, datetime) VALUES(?, ?, ?, ?, CURRENT_TIMESTAMP)",
                   session["user_id"], quote["symbol"], -abs(int(request.form.get("shares"))), quote["price"])

        # Redirect user to home page
        return redirect("/")

    else:
        return render_template("sell.html", all_stocks=all_stocks)