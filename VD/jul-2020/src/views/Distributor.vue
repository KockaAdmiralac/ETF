<template>
<section>
  <h1>Dostavljač</h1>
  <form @submit.prevent="submit()">
    <p>
      <label for="name">Naziv</label>
      <input type="text" name="name" id="name" v-model="name" required>
    </p>
    <p>
      <label for="quantity">Količina</label>
      <input type="number" name="quantity" id="quantity" v-model="quantity" required>
    </p>
    <p>
      <label for="date">Datum</label>
      <input type="date" name="date" id="date" v-model="date" required>
    </p>
    <input type="submit" value="Unesi">
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
</style>

<script>
export default {
  name: 'Distributor',
  data () {
    return {
      name: '',
      quantity: '',
      date: '',
      products: []
    }
  },
  created () {
    this.products = JSON.parse(localStorage.getItem('products') || '[]')
  },
  methods: {
    submit () {
      if (
        this.name === '' ||
        this.quantity === '' ||
        this.date === ''
      ) {
        return
      }
      const product = this.products.find(({ name }) => name === this.name)
      if (product) {
        product.quantity += Number(this.quantity)
        product.date = this.date
      } else {
        this.products.push({
          name: this.name,
          quantity: Number(this.quantity),
          date: this.date
        })
      }
      localStorage.setItem('products', JSON.stringify(this.products))
    }
  }
}
</script>
