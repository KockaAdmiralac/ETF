<template>
<section>
  <h1>Posetilac: {{username}}</h1>
  <table>
    <tr>
      <th>Identifikacioni broj</th>
      <th>Početna destinacija</th>
      <th>Krajnja destinacija</th>
      <th>Trajanje u minutima</th>
      <th>Akcija</th>
    </tr>
    <tr v-for="flight of flights" :key="flight.id" :class="flight.duration > 200 ? 'long' : ''">
      <td>{{flight.id}}</td>
      <td>{{flight.start}}</td>
      <td>{{flight.end}}</td>
      <td>{{flight.duration}}</td>
      <td><button @click="book(flight)">Rezerviši</button></td>
    </tr>
  </table>
  <p class="error">{{error}}</p>
</section>
</template>

<style scoped>
.error {
  color: red;
}
.long {
  color: green;
  font-weight: bold;
}
</style>

<script>
export default {
  name: 'Visitor',
  data() {
    return {
      error: '',
      flights: [],
      reservations: [],
      username: ''
    }
  },
  created() {
    this.username = localStorage.getItem('user')
    this.flights = JSON.parse(localStorage.getItem('flights') || '[]')
    this.reservations = JSON.parse(localStorage.getItem('reservations') || '{}')
  },
  methods: {
    book(flight) {
      const reservations = this.reservations[this.username] || []
      const reservation = reservations.find(({id}) => id === flight.id)
      if (reservation) {
        this.error = 'Već ste rezervisali taj let.'
        return
      }
      reservations.push({...flight})
      this.reservations[this.username] = reservations
      localStorage.setItem('reservations', JSON.stringify(this.reservations))
      this.$router.push('reservations')
    }
  }
}
</script>
