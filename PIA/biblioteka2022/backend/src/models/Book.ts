import {Schema, model} from 'mongoose';

const Book = new Schema({
    author: {
        type: String
    },
    deadline: {
        type: String
    },
    id: {
        type: String
    },
    person: {
        type: String
    },
    title: {
        type: String
    }
});

export default model('Books', Book, 'books');
