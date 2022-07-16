<template>
<main>
  <h1>Login</h1>
  <form @submit.prevent="login()">
    <p>
      <label for="username">Username</label>
      <input type="text" name="username" id="username" v-model="username" required>
    </p>
    <p>
      <label for="password">Password</label>
      <input type="password" name="password" id="password" v-model="password" required>
    </p>
    <input type="submit" value="Login">
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
  name: 'Home',
  data() {
    return {
      username: '',
      password: '',
      error: '',
      users: []
    }
  },
  created() {
    const savedUsers = localStorage.getItem('users')
    this.users = savedUsers ? JSON.parse(savedUsers) : [
      {
        name: 'Petar',
        surname: 'Petrović',
        username: 'pera',
        password: 'pera123',
        type: 'employee'
      },
      {
        name: 'Nikola',
        surname: 'Nikolić',
        username: 'nikola',
        password: 'nikola123',
        type: 'visitor'
      },
      {
        name: 'Lazar',
        surname: 'Lazić',
        username: 'laza',
        password: 'laza123',
        type: 'visitor'
      }
    ]
  },
  methods: {
    login() {
      if (this.username === '') {
        this.error = 'Unesite korisničko ime.'
        return
      }
      if (this.password === '') {
        this.error = 'Unesite lozinku.'
        return
      }
      const user = this.users.find(({username}) => username === this.username)
      if (!user) {
        this.error = 'Korisničko ime ne postoji u sistemu.'
        return
      }
      const {username, password, type} = user
      if (password !== this.password) {
        this.error = 'Pogrešna lozinka.'
        return
      }
      this.$router.push(type)
      localStorage.setItem('user', username)
    }
  }
}
</script>
