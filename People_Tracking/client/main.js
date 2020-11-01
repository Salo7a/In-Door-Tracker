import {Template} from 'meteor/templating';
import 'bootstrap/dist/css/bootstrap.min.css';

import './main.html';

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

const room_map = {
  '00': { top: '60%', left: '50%'},
  '01': { top: '43%', left: '50%'},
  '02': { top: '23%', left: '50%'},
  '1': { top: '62%', left: '80%'},
  '2': { top: '45%', left: '80%'},
  '3': { top: '28%', left: '80%'},
  '4': { top: '10%', left: '80%'},
  '5': { top: '62%', left: '20%'},
  '6': { top: '45%', left: '20%'},
  '7': { top: '28%', left: '20%'},
  '8': { top: '10%', left: '20%'},
}

Template.body.events({
    'click .connectBtn'(event, instance) {
        console.log('clicked');

        // Get a reference to the database service
        let datapoint = firebase.database().ref();
        let data = datapoint.child("RSSIs");

        data.on('value', (snapshot) => {
            let rssi_values = snapshot.val().split(" ").map(Number);
            rssi_values.pop();

            console.log(rssi_values);

            // Classify the location based on the scanned networks
            let location = getLocation(rssi_values);

            if (rssi_values[3] < -50)
            {
                location = 3;
            }

            $(".human").css({
                top: room_map[location]['top'],
                left: room_map[location]['left']
            });

        });

    },
});


Template.body.events({
  'submit .new-move'(event) {
    // Prevent default browser form submit
    event.preventDefault();

    // Get value from form element
    const target = event.target;
    const number = target.room_number.value;

    $(".human").css({
        top: room_map[number]['top'],
        left: room_map[number]['left']
    });

    // Clear form
    target.room_number.value = '';
  },
});

// Function to apply the ML hypothesis function to get the current room location
const getLocation = (networks) => {
    // equation here
    return {}
}