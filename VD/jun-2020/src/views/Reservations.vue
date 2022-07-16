<template>
<main>
  <h1>Rezervacije korisnika: {{username}}</h1>
  <table>
    <thead>
      <tr>
        <th>Identifikacioni broj</th>
        <th>Početna destinacija</th>
        <th>Krajnja destinacija</th>
        <th>Trajanje u minutima</th>
      </tr>
    </thead>
    <tbody>
      <tr v-for="reservation of reservations" :key="reservation.id">
        <td>{{reservation.id}}</td>
        <td>{{reservation.start}}</td>
        <td>{{reservation.end}}</td>
        <td>{{reservation.duration}}</td>
      </tr>
    </tbody>
  </table>
  <button @click="back()">Nazad</button>
</main>
</template>

<script>
export default {
  name: 'Reservations',
  data() {
    return {
      reservations : [],
      username: ''
    }
  },
  created() {
    this.username = localStorage.getItem('user')
    this.reservations = JSON.parse(localStorage.getItem('reservations'))[this.username]
  },
  methods: {
    back() {
      this.$router.back()
    }
  }
}
</script>
