import {Schema, model} from 'mongoose';

const Extra = new Schema({
    amount: {
        type: Number
    },
    id: {
        type: Number
    },
    name: {
        type: String
    }
});

export default model('Extras', Extra, 'extras');
