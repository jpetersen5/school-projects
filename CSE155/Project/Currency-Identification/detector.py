#import os
import json
import cv2 as cv
#from imgfunc import removeBG
from imgfunc import crop, overlap
from roboflow import Roboflow
#from PIL import Image

# load single-coin model trained from Roboflow
rf_single = Roboflow(api_key="LXDXfUz9i5E69TwyAm9t")
project_single = rf_single.workspace().project("currency-detection-olpia")
model_single = project_single.version(1).model

# load multi-coin model train from Roboflow
rf_multi = Roboflow(api_key="aYdpTiPcCMBgI3w7asbA")
project_multi = rf_multi.workspace().project("coin-counter-3")
model_multi = project_multi.version(3).model

f = open("cat_to_name.json")
names = json.load(f)
f.close()
colors = {"penny":(62,93,146),"nickel":(89,94,93),"dime":(150,156,159),"quarter":(126,122,117),"half_dollar":(187,198,196),"dollar":(65,70,69)}

def static(img):
    #im = Image.open(img)
    #im = im.resize((500,400))
    #im.save('static/temp/test.jpg',"jpeg")
    #img = 'static/temp/test.jpg'
    cv.imwrite(img,crop(img))
    prediction = model_single.predict(img)
    #prediction.save(img)
    result = prediction.json()['predictions'][0]
    info = str(names[str(result['top'])]).split(',')
    info[2] = info[2].capitalize()
    info.append(str(round(100 * result['confidence'],2)) + "%")
    print(info)
    return info

def static_multi(img):
    prediction = model_multi.predict(img)
    results = prediction.json()['predictions']
    temp = cv.imread(img)
    for i, result1 in enumerate(results):
        for j, result2 in enumerate(results):
            if i != j:
                if overlap(result1['x'],result1['y'],result2['x'],result2['y']):
                    del results[j]
    count = 1
    for result in results:
        top_left = (round(result['x'] - result['width'] / 2 + 10), round(result['y'] - result['height'] / 2 + 10))
        bottom_right = (round(result['x'] + result['width'] / 2 - 10), round(result['y'] + result['height'] / 2 - 10))
        predictedclass = str(result['class'])
        classcolor = colors[predictedclass]
        font_scale = 0.0025 * (result['height'] + result['width'])
        cv.rectangle(temp,top_left,bottom_right,classcolor,round(3*font_scale))
        text = predictedclass+": "+str(round(result['confidence'],2))
        font = cv.FONT_HERSHEY_SIMPLEX
        font_thickness = 2
        text_size, _ = cv.getTextSize(text, font, font_scale, font_thickness)
        text_width, text_height = text_size
        text_position = (top_left[0],top_left[1]+text_height)
        padding = 2
        bg_top_left = (text_position[0] - padding, text_position[1] - text_height - padding)
        bg_bottom_right = (text_position[0] + text_width + padding, text_position[1] + padding)
        cv.rectangle(temp, bg_top_left, bg_bottom_right, classcolor, -1)
        cv.putText(temp,text,text_position,font,font_scale,(0,0,0),round(font_thickness*font_scale))
        center = (round(result['x']-15*font_scale),round(result['y']+15*font_scale))
        cv.putText(temp,str(count),center,font,2*font_scale,(0,0,255),round(2*font_thickness*font_scale))
        count = count + 1
    cv.imwrite(img,temp)
    return results

""" Live feed detection (works but not viable)
def live():
    # begin camera feed
    cam = cv.VideoCapture(0)
    if not cam.isOpened():
        print("Cannot open camera")
        exit()
    while True:
        # frame by frame
        ret, frame = cam.read()
        # check if frame is read correctly
        if not ret:
            print("Can't receive frame (stream end?). Exiting ...")
            break

        # display
        # convert to gray -> binary -> contours (bounding shapes)
        gray = cv.cvtColor(frame, cv.COLOR_BGR2GRAY)
        thresh = cv.threshold(gray, 0, 255, cv.THRESH_BINARY_INV + cv.THRESH_OTSU)[1]
        contours = cv.findContours(thresh, cv.RETR_TREE, cv.CHAIN_APPROX_TC89_L1)
        contours = contours[0] if len(contours) == 2 else contours[1]
        # for each contour, make a bounding box
        for i in contours:
            x,y,w,h = cv.boundingRect(i)
            # ignore if box isn't big enough
            if ((w >= 30 and h >= 30) and (w <= 500 and h <= 500)):
                # crop bounding object
                cropframe = removeBG(frame[y:y+h,x:x+w])
                # save temp file (for prediction)
                cv.imwrite('img/temp_crop.jpg',cropframe)
                # run prediction
                prediction = model.predict('img/temp_crop.jpg')
                try: # remove temp file
                    os.remove('img/temp_crop.jpg')
                except: pass
                # collect predictions
                result = prediction.json()['predictions'][0]
                # draw box
                cv.rectangle(frame, (x, y), (x + w, y + h), (0,0,255), 4)
                # label box with class prediction
                cv.putText(frame, str(names[str(result['top'])]) + ": " + str(result['confidence']), (x, y-10), cv.FONT_HERSHEY_SIMPLEX, 0.3, (0,0,255), 1)
        cv.imshow('frame (press q to end)', frame)

        # check for quit
        if cv.waitKey(1) == ord('q'):
            break

    # end live capture
    cam.release()
    cv.destroyAllWindows()
"""

