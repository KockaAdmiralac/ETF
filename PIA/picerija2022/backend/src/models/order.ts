import {Schema, model} from 'mongoose';

const Order = new Schema({
    extras: {
        type: Array
    },
    id: {
        type: Number
    },
    size: {
        type: String
    },
    status: {
        type: String
    },
    user: {
        type: String
    }
});

export default model('Orders', Order, 'orders');
