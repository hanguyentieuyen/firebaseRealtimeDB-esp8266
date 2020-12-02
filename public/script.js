
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
    
    var root = firebase.database().ref();
/*******************************************************************************/

function onoff(){
  currentValue = document.getElementById('onoff').value;
  if(currentValue == "OFF"){
      document.getElementById("onoff").value="ON";
      document.getElementById('circle').style.backgroundColor = "#f1c40f"
      document.getElementById('circle').style.boxShadow = "0 0 20px 5px #f1c40f"; 
      root.child("LED/ledStatus").set("1");
  }else{
      document.getElementById("onoff").value="OFF";
      document.getElementById('circle').style.backgroundColor = "";
      document.getElementById('circle').style.boxShadow = ""; 
      root.child("LED/ledStatus").set("0");
  }
}


function onoff1(){
    currentValue = document.getElementById('onoff1').value;
    if(currentValue == "OFF"){
        document.getElementById("onoff1").value="ON";
        document.getElementById('circle1').style.backgroundColor = "#f1c40f"
        document.getElementById('circle1').style.boxShadow = "0 0 20px 5px #f1c40f"; 
        root.child("LED/ledStatus").set("1");
    }else{
        document.getElementById("onoff1").value="OFF";
        document.getElementById('circle1').style.backgroundColor = "";
        document.getElementById('circle1').style.boxShadow = ""; 
        root.child("LED/ledStatus").set("0");
    }
}



/********Đọc nhiệt độ => get data về hiển thị**********/
const temp = document.getElementById('textTemp');
const hum = document.getElementById('textHum');

var rootChild = firebase.database().ref().child('DHT11');
rootChild.on('child_added',function(snapshot){
// temp.innerText = JSON.stringify(snapshot.val(),null,3)
temp.innerText = snapshot.val();
hum.innerText  = snapshot.val();
})






