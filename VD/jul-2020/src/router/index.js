import { createRouter, createWebHistory } from 'vue-router'
import Distributor from '../views/Distributor.vue'
import Home from '../views/Home.vue'
import Pharmacist from '../views/Pharmacist.vue'

const routes = [
  {
    path: '/',
    name: 'Home',
    component: Home
  },
  {
    path: '/distributor',
    name: 'Distributor',
    component: Distributor
  },
  {
    path: '/pharmacist',
    name: 'Pharmacist',
    component: Pharmacist
  }
]

const router = createRouter({
  history: createWebHistory(process.env.BASE_URL),
  routes
})

export default router
