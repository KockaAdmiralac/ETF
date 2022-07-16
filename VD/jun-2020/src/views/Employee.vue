<template>
<main>
  <h1>Zaposleni</h1>
  <form @submit.prevent="submit()">
    <p>
      <label for="id">Identifikacioni broj</label>
      <input type="number" name="id" id="id" v-model="id" required>
    </p>
    <p>
      <label for="start">Početna destinacija</label>
      <input type="text" name="start" id="start" v-model="start" required>
    </p>
    <p>
      <label for="end">Krajnja destinacija</label>
      <input type="text" name="end" id="end" v-model="end" required>
    </p>
    <p>
      <label for="duration">Trajanje u minutima</label>
      <input type="number" name="duration" id="duration" v-model="duration" required>
    </p>
    <input type="submit" value="Unesi">
    <p class="error">{{error}}</p>
  </form>
</main>
</template>

<style scoped>
label {
  padding-right: 10px;
}
p {
  margin: 0;
  margin-bottom: 2px;
}
.error {
  color: red;
}
</style>

<script>
export default {
  name: 'Employee',
  data() {
    return {
      id: '',
      start: '',
      end: '',
      duration: '',
      error: '',
      flights: []
    }
  },
  created() {
    this.flights = JSON.parse(localStorage.getItem('flights') || '[]')
  },
  methods: {
    submit() {
      if (
        this.id === '' ||
        this.start === '' ||
        this.end == '' ||
        this.duration == ''
      ) {
        return
      }
      const flight = this.flights.find(({id}) => id === Number(this.id))
      if (flight) {
        this.error = 'Let sa zadatim identifikatorom već postoji u sistemu.'
        return
      }
      this.flights.push({
        duration: Number(this.duration),
        end: this.end,
        id: Number(this.id),
        start: this.start
      })
      localStorage.setItem('flights', JSON.stringify(this.flights))
    }
  }
}
</script>
