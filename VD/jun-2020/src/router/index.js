import { createRouter, createWebHistory } from 'vue-router'
import Employee from '../views/Employee.vue'
import Home from '../views/Home.vue'
import Reservations from '../views/Reservations.vue'
import Visitor from '../views/Visitor.vue'

const routes = [
  {
    path: '/',
    name: 'Home',
    component: Home
  },
  {
    path: '/employee',
    name: 'Employee',
    component: Employee
  },
  {
    path: '/visitor',
    name: 'Visitor',
    component: Visitor
  },
  {
    path: '/reservations',
    name: 'Reservations',
    component: Reservations
  }
]

const router = createRouter({
  history: createWebHistory(process.env.BASE_URL),
  routes
})

export default router
