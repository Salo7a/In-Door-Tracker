import { Template } from 'meteor/templating';
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

let scanned_networks = { }

const room_map = {
  '00': { top: '55%', left: '50%'},
  '01': { top: '20%', left: '50%'},
  1: { top: '64%', left: '80%'},
  2: { top: '50%', left: '80%'},
  3: { top: '36%', left: '80%'},
  4: { top: '22%', left: '80%'},
  5: { top: '8%', left: '80%'},
  6: { top: '64%', left: '20%'},
  7: { top: '50%', left: '20%'},
  8: { top: '36%', left: '20%'},
  9: { top: '22%', left: '20%'},
  10: { top: '8%', left: '20%'},
}

Template.body.events({
    'click .connectBtn'(event, instance) {
        console.log('clicked');

        // Get a reference to the database service
        let datapoint = firebase.database().ref();

        datapoint.on('value', function(snapshot) {
            snapshot.forEach(function(childSnapshot) {
                scanned_networks[childSnapshot.key] = childSnapshot.val();
            });
            console.log(scanned_networks);
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

// Template.hello.onCreated(function helloOnCreated() {
//   // counter starts at 0
//   this.counter = new ReactiveVar(0);
// });
//
// Template.hello.helpers({
//   counter() {
//     return Template.instance().counter.get();
//   },
// });
//
// Template.hello.events({
//   'click button'(event, instance) {
//     // increment the counter when button is clicked
//     instance.counter.set(instance.counter.get() + 1);
//   },
// });
