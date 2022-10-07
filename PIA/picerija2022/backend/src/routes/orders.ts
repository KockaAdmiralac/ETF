import Extra from '../models/extra';
import Order from '../models/order';
import {Router} from 'express';

const router = Router();

router.get('/', async function(req, res) {
    const {user} = req.query;
    const condition = user ? {user} : {};
    const orders = await Order.find(condition);
    res.json({orders});
});

router.post('/', async function(req, res) {
    const {extras, size, user} = req.body;
    await Order.insertMany([{
        extras,
        size,
        status: 'nova',
        user
    }]);
    res.json({message: 'OK'});
});

router.patch('/', async function(req, res) {
    const {id, status} = req.body;
    const order = await Order.findOne({_id: id});
    if (!order) {
        res.status(400).json({
            message: 'Unknown order.'
        });
        return;
    }
    await Order.updateOne({_id: id}, {status});
    await Extra.updateMany(
        {
            name: {
                $in: order.extras
            }
        },
        {
            $inc: {
                amount: -1
            }
        }
    );
    res.json({message: 'OK'});
});

export default router;
