<template>
<section>
  <h1>Apotekar</h1>
  <table>
    <thead>
      <tr>
        <th>Naziv</th>
        <th>Količina</th>
        <th>Datum</th>
        <th>Akcija</th>
      </tr>
    </thead>
    <tbody>
      <tr v-for="product of products" :key="product.name" :class="today(product) ? 'today' : ''">
        <td>{{product.name}}</td>
        <td>{{product.quantity}}</td>
        <td>{{product.date}}</td>
        <td><button @click="remove(product)">Ukloni</button></td>
      </tr>
    </tbody>
  </table>
</section>
</template>

<style scoped>
.today {
  color: green;
  font-weight: bold;
}
</style>

<script>
export default {
  name: 'Pharmacist',
  data () {
    return {
      products: []
    }
  },
  created () {
    this.products = JSON.parse(localStorage.getItem('products') || '[]')
  },
  methods: {
    remove (product) {
      console.log(product, this.products)
      this.products = this.products.filter(({ name }) => name !== product.name)
      localStorage.setItem('products', JSON.stringify(this.products))
    },
    today (product) {
      const today = new Date()
      const productDate = new Date(product.date)
      return productDate.toDateString() === today.toDateString()
    }
  }
}
</script>
