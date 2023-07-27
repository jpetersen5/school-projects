
function camera(){
    var but = document.getElementById("but");
    var stop = document.getElementById("stop");
    var video = document.getElementById("vid");
    var canvas = document.getElementById("canvas");
    var preview = document.getElementById("previewcam");
    var capture = document.getElementById("capture");
    vid.muted = true;

    but.addEventListener("click", () => {
        // Accessing the user camera and video.
        var mediaDevices = navigator.mediaDevices;
        mediaDevices
            .getUserMedia({
            video: true,
        })
        .then((stream) => {
            // Changing the source of video to current stream.
            video.srcObject = stream;
            video.addEventListener("loadedmetadata", () => {
                video.play();
            });
        })
        .catch(alert);
    
        but.style.display = "none";
        stop.style.display = "inline-block";
        capture.style.display = "inline-block";
        send.style.display = "inline-block";
    });
    stop.addEventListener("click", () => {
        video.srcObject.getTracks().forEach(track => track.stop());
        but.style.display = "inline-block";
        stop.style.display = "none";
        capture.style.display = "none";
        send.style.display = "none";
        divvid.style.display = "block";
        results.style.display = "none";
    });
    capture.addEventListener("click", () => {
        let context = canvas.getContext("2d");
        context.drawImage(video, 0, 0, canvas.width, canvas.height);
        canvas.toBlob(upload, "image/jpeg");
        const data = canvas.toDataURL("image/jpeg");
        preview.src = data;
        divvid.style.display = "none";
        results.style.display = "block";
    });
}

function upload(file) {
    var form = new FormData();
    form.append("screencap", file);
    
    fetch('/webcam', {
        method: 'POST',
        body: form
    })
    .then(response => {
        if (response.ok) {
            return response.text();
        } else {
            throw new Error('Error uploading the image');
        }
    })
    .then(data => {
        console.log('Image uploaded successfully:', data);
    })
    .catch(error => {
        console.error('Error uploading the image:', error);
    });
}

function file(){
    var fr = new FileReader();
    // var filename = document.getElementById("image").files[0].name;
    var file = document.getElementById("image").files[0];
    var read = fr.readAsDataURL(file);
    var temp = document.createElement("img");
    temp.src = read;
    console.log(temp.src);
    console.log(file);

    // var out = document.getElementById("results");
    // out.appendChild(temp);

    // console.log(out)
}

image.onchange = evt => {
    const [file] = image.files
    if (file) {
        preview.style.display = "inline-block";
        preview.src = URL.createObjectURL(file);
    }
}

function toggleMulti() {
    var form = document.getElementById("upload");
    var toggleButton = document.getElementById("toggle");

    if (form.action.endsWith("/fileupload")) {
        form.action = "/multiupload";
        toggleButton.innerHTML = "<b>Switch to Single Coin</b>";
    } else {
        form.action = "/fileupload";
        toggleButton.innerHTML = "<b>Switch to Multiple Coins</b>";
    }
}


function submitForm() {
    const form = document.getElementById("coin-form");
    const formData = new FormData(form);

    fetch('/process', {
        method: 'POST',
        body: formData
    })
    .then(response => response.text())
    .then(data => {
        document.getElementById('output').innerHTML = data;
    })
    .catch(error => {
        console.error('Error fetching data:', error);
    });
}