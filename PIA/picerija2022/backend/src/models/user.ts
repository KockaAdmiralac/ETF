import {Schema, model} from 'mongoose';

const User = new Schema({
    // eslint-disable-next-line camelcase
    first_name: {
        type: String
    },
    // eslint-disable-next-line camelcase
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
