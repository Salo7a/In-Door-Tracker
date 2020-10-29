import { Template } from 'meteor/templating';
import { ReactiveVar } from 'meteor/reactive-var';

import './main.html';

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
