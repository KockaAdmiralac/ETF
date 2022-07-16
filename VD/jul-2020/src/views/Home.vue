<template>
<section>
  <h1>Početna stranica</h1>
  <form @submit.prevent="login()">
    <p>
      <label for="username">Korisničko ime</label>
      <input type="text" name="username" id="username" v-model="username" required>
    </p>
    <p>
      <label for="password">Lozinka</label>
      <input type="password" name="password" id="password" v-model="password" required>
    </p>
    <p>
      <label for="type-distributor">Dostavljač</label>
      <input type="radio" name="type" id="type-distributor" v-model="type" value="distributor">
      <label for="type-pharmacist">Apotekar</label>
      <input type="radio" name="type" id="type-pharmacist" v-model="type" value="pharmacist">
    </p>
    <p><input type="submit" value="Uloguj se"></p>
    <p class="error">{{error}}</p>
  </form>
</section>
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
  font-weight: bold;
}
</style>

<script>
export default {
  name: 'Home',
  data () {
    return {
      username: '',
      password: '',
      type: '',
      error: '',
      users: []
    }
  },
  created () {
    const savedUsers = localStorage.getItem('users')
    this.users = savedUsers ? JSON.parse(savedUsers) : [
      {
        name: 'Petar',
        surname: 'Jović',
        username: 'pera',
        password: 'pera123',
        type: 'distributor'
      },
      {
        name: 'Milica',
        surname: 'Nikolić',
        username: 'mica',
        password: 'mica123',
        type: 'pharmacist'
      },
      {
        name: 'Jovan',
        surname: 'Lazić',
        username: 'jova',
        password: 'jova123',
        type: 'pharmacist'
      }
    ]
  },
  methods: {
    login () {
      if (this.username === '') {
        this.error = 'Unesite korisničko ime.'
        return
      }
      if (this.password === '') {
        this.error = 'Unesite lozinku.'
        return
      }
      if (this.type === '') {
        this.error = 'Izaberite tip.'
        return
      }
      const user = this.users.find(({ username }) => username === this.username)
      if (!user) {
        this.error = 'Korisničko ime ne postoji u sistemu.'
        return
      }
      const { username, password, type } = user
      if (password !== this.password) {
        this.error = 'Pogrešna lozinka.'
        return
      }
      if (type !== this.type) {
        this.error = 'Pogrešan tip.'
        return
      }
      this.$router.push(type)
      localStorage.setItem('user', username)
    }
  }
}
</script>
