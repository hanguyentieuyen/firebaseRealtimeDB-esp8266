var firebaseConfig = {
  apiKey: "AIzaSyC8A5duP8DLcd_4sHJyaZxHtWoOy-kIx00",
  authDomain: "esprealtimedb.firebaseapp.com",
  databaseURL: "https://esprealtimedb.firebaseio.com",
  projectId: "esprealtimedb",
  storageBucket: "esprealtimedb.appspot.com",
  messagingSenderId: "573051056608",
  appId: "1:573051056608:web:7cca5e2e240373a0ccbb85",
  measurementId: "G-QNSLTNSM2C"
};
// Initialize Firebase
firebase.initializeApp(firebaseConfig);


/********************Read status LED on realtimeDB*********************/
var root = firebase.database().ref('LED');

root.child('ledStatus').on ('value', function(snapshot) {
  var Status = snapshot.val();
  if ( Status == "1")  {
    document.getElementById("onoff").value = "ON";
    document.getElementById('circle').style.backgroundColor = "#f1c40f"
    document.getElementById('circle').style.boxShadow = "0 0 20px 5px #f1c40f";
  } else {
    document.getElementById("onoff").value = "OFF";
    document.getElementById('circle').style.backgroundColor = "";
    document.getElementById('circle').style.boxShadow = "";
  }
})

root.child('ledStatus1').on ('value', function(snapshot) {
  var Status1 = snapshot.val();
  if ( Status1 == "1")  {
    document.getElementById("onoff1").value = "ON";
    document.getElementById('circle1').style.backgroundColor = "#f1c40f"
    document.getElementById('circle1').style.boxShadow = "0 0 20px 5px #f1c40f";
  } else {
    document.getElementById("onoff1").value = "OFF";
    document.getElementById('circle1').style.backgroundColor = "";
    document.getElementById('circle1').style.boxShadow = "";
  }
})
/********************Write status LED on realtimeDB******************/
function onoff() {
  currentValue = document.getElementById('onoff').value;
  if (currentValue == "OFF") {
    document.getElementById("onoff").value = "ON";
    document.getElementById('circle').style.backgroundColor = "#f1c40f"
    document.getElementById('circle').style.boxShadow = "0 0 20px 5px #f1c40f";
    root.child("ledStatus").set("1");
  } else {
    document.getElementById("onoff").value = "OFF";
    document.getElementById('circle').style.backgroundColor = "";
    document.getElementById('circle').style.boxShadow = "";
    root.child("ledStatus").set("0");
  }
}

function onoff1() {
  currentValue = document.getElementById('onoff1').value;
  if (currentValue == "OFF") {
    document.getElementById("onoff1").value = "ON";
    document.getElementById('circle1').style.backgroundColor = "#f1c40f"
    document.getElementById('circle1').style.boxShadow = "0 0 20px 5px #f1c40f";
    root.child("ledStatus1").set("1");
  } else {
    document.getElementById("onoff1").value = "OFF";
    document.getElementById('circle1').style.backgroundColor = "";
    document.getElementById('circle1').style.boxShadow = "";
    root.child("ledStatus1").set("0");
  }
}

/*******************Đọc nhiệt độ => get data về hiển thị**********/
const temp = document.getElementById('textTemp');
const hum = document.getElementById('textHum');

var rootTemp = firebase.database().ref('DHT11').child('Temp');
rootTemp.on ('value', function(snapshot) {
  temp.innerText = snapshot.val();
})

var rootHum = firebase.database().ref('DHT11').child('Hum');
rootHum.on ('value', function(snapshot) {
  hum.innerText = snapshot.val();
})
