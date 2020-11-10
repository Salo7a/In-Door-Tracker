const {spawn} = require('child_process');
let location ;

// Load Library
const firebase = require("firebase/app");

// Add the Firebase products that you want to use
require("firebase/auth");
require("firebase/firestore");
require("firebase/database");

let firebaseConfig = {
    apiKey: "AIzaSyDyB24gmqLcQzHpSAmJCt0_A1lCkUfqHw4",
    authDomain: "tracking-a-person-using-wifi.firebaseapp.com",
    databaseURL: "https://tracking-a-person-using-wifi.firebaseio.com",
    projectId: "tracking-a-person-using-wifi",
    storageBucket: "tracking-a-person-using-wifi.appspot.com",
    messagingSenderId: "495213011124",
    appId: "1:495213011124:web:bfd9ec59e6febf344a77e1",
    measurementId: "G-P0XHXV6GZ5"
};

firebase.initializeApp(firebaseConfig);
let datapoint = firebase.database().ref();
let data = datapoint.child("RSSIs");
let locsnap = datapoint.child("location");

async function getLocation(data){
    console.log(data);
    const python = await spawn('python', ['localize.py', 'model.joblib', data[0], data[1], data[2],data[3], data[4],data[5], data[6], data[7], data[8]]);
    await python.stdout.on('data', async function (data) {
        console.log('Pipe data from python script ...');
        location = await parseInt(data.toString()[1]);
        console.log("the location is", location);
        locsnap.set(location)
    });
};

// Get a reference to the database service

// console.log(locsnap);
data.on('value', async (snapshot) => {
    let rssi_values = snapshot.val().split(" ").map(Number);
    rssi_values.pop();

    // console.log(rssi_values);

    // Classify the location based on the scanned networks
    let location = await getLocation(rssi_values);
    // console.log(location)
    // locsnap.set(8);
    

});
