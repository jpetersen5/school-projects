import os
import detector
from flask import Flask, render_template, request, redirect, url_for, flash
from werkzeug.utils import secure_filename
from changecalculator import findChange

UPLOAD_FOLDER = os.path.join('static','temp')
ALLOWED_EXTENSIONS = {'png', 'jpg', 'jpeg'}
values = {"penny":0.01,"nickel":0.05,"dime":0.10,"quarter":0.25,"half_dollar":0.5,"dollar":1.0}

app = Flask(__name__, template_folder="Templates", static_folder="static")
app.secret_key = 'weee'
app.config['UPLOAD_FOLDER'] = UPLOAD_FOLDER

def allowed_file(filename):
    return '.' in filename and \
           filename.rsplit('.', 1)[1].lower() in ALLOWED_EXTENSIONS

@app.route("/")
def default():
    return redirect(url_for('home'))

@app.route("/home")
def home():
    return render_template("home.html")

@app.route("/webcam", methods = ['GET','POST'])
def webcam():
    if request.method == 'POST':
        f = request.files.get('screencap')
        if f:
            image = os.path.join(app.config['UPLOAD_FOLDER'],(secure_filename(f.filename))+".jpg").replace("\\",'/')
            f.save(image)
            info = detector.static(image)
            flash("Value: " + info[0])
            flash("Currency: " + info[1])
            flash("Country: " + info[2])
            flash("Confidence: " + info[3])
            info2 = "Value: " + info[0] + "Currency: " + info[1] + "Country: " + info[2] + "Confidence: " + info[3]
            return render_template("webcam.html", info=info2)
        else:
            flash('Please select a valid file!')
    return render_template("webcam.html")

@app.route("/fileupload", methods = ['GET','POST'])
def fileupload():
    if request.method == 'POST':
        f = request.files['image']
        if f and allowed_file(f.filename):
            image = os.path.join(app.config['UPLOAD_FOLDER'],secure_filename(f.filename)).replace("\\",'/')
            f.save(image)
            info = detector.static(image)
            flash("Value: " + info[0])
            flash("Currency: " + info[1])
            flash("Country: " + info[2])
            flash("Confidence: " + info[3])
            return render_template("fileupload.html", user_image = image)
        else:
            flash('Please select a valid file!')
    return render_template("fileupload.html")

@app.route("/multiupload", methods = ['GET','POST'])
def multiupload():
    if request.method == 'POST':
        f = request.files['image']
        if f and allowed_file(f.filename):
            image = os.path.join(app.config['UPLOAD_FOLDER'],secure_filename(f.filename)).replace("\\",'/')
            f.save(image)
            coins = detector.static_multi(image)
            count = {"penny":0,"nickel":0,"dime":0,"quarter":0}
            value = 0
            for coin in coins:
                count[coin['class']] = count[coin['class']] + 1
                value = value + values[coin['class']]
            toFlash = ""
            for coin in count:
                toFlash = toFlash + str(count[coin]) + " " + coin + "s, "
            flash(toFlash)
            flash("Total: $" + str(round(value,2)))
            return render_template("fileupload.html", user_image = image, quarters = count["quarter"], dimes = count["dime"], nickels = count["nickel"], pennies = count["penny"])
        else:
            flash('Please select a valid file!')
    return render_template("fileupload.html")

@app.route('/process', methods=['POST'])
def process():
    input_value = request.form.get('input_value')
    quarters = int(request.form['quarters'])
    dimes = int(request.form['dimes'])
    nickels = int(request.form['nickels'])
    pennies = int(request.form['pennies'])
    works, coins, leftovervalue = findChange(input_value,quarters,dimes,nickels,pennies)
    if (works):
        output = "It worked! "
    else:
        output = f"${leftovervalue} left! "
    output = output + f"Quarters: {coins['quarter']}, Dimes: {coins['dime']}, Nickels: {coins['nickel']}, Pennies: {coins['penny']}"
    return output

if __name__ == '__main__':
   app.run(debug = True)