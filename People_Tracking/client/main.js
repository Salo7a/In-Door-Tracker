import {Template} from 'meteor/templating';
import 'bootstrap/dist/css/bootstrap.min.css';

import './main.html';
import snap from "app-builder-lib/out/targets/snap";

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
  '1': { top: '77%', left: '73%'},
  '2': { top: '47%', left: '73%'},
  '3': { top: '14%', left: '73%'},
  '4': { top: '75%', left: '50%'},
  '5': { top: '43%', left: '50%'},
  '6': { top: '12%', left: '50%'},
  '7': { top: '95%', left: '50%'},
  // '4': { top: '10%', left: '80%'},
  // '5': { top: '62%', left: '20%'},
  // '6': { top: '45%', left: '20%'},
  // '8': { top: '10%', left: '20%'},
}

let rooms = [1, 2, 3];
let location;
let tempRoom;

Template.body.events({
    'click .connectBtn'(event, instance) {
        console.log('Connect!');

        let human = document.getElementsByClassName("human")[1];

        // Get a reference to the database service
        let datapoint = firebase.database().ref();
        let data = datapoint.child("location");

        // Get initial room
        datapoint.once('value',  function(snapshot) {
            snapshot.forEach(function(childSnapshot) {
                if (childSnapshot.key === 'location')
                {
                    location = childSnapshot.val();
                    console.log("location", location);
                }
            });
        });

        data.on('value', (snapshot) => {
            tempRoom = snapshot.val();
            console.log("tempRoom ", tempRoom);

            // Check if old location and new location in rooms
            if (rooms.includes(location)) {
                if (!rooms.includes(tempRoom)) {
                    location = tempRoom;
                    updateLocation(location);
                }
            }
            else {
                location = tempRoom;
                updateLocation(location);
            }
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

const updateLocation = (loc) => {
    $(".human").css({
        top: room_map[loc]['top'],
        left: room_map[loc]['left']
    });
}