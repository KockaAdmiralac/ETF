import {Schema, model} from 'mongoose';

const User = new Schema({
    first_name: {
        type: String
    },
    last_name: {
        type: String
    },
    password: {
        type: String
    },
    type: {
        type: String
    },
    username: {
        type: String
    }
});

export default model('Users', User, 'users');
