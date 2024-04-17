# IS1 project

The project is about building a bank's information system as an HTTP API using
JAX-RS, with three subsystems with separate databases that communicate with the
server over JMS (and periodically synchronize), and an HTTP client built using
[Retrofit](https://square.github.io/retrofit/) to provide an interface for the
bank operations. You can read the
[project specification](https://web.archive.org/web/20220629223853/http://si3is1.etf.rs/Domaci%20zadatak/13E114IS1_domaci_21_22.pdf)
for more details.

## Structure
- `Server`: JAX-RS server project, as well as some shared classes (entities,
  commands) symlinked in other projects
- `SubsystemX`: Subsystem projects, handling requests over JMS and managing
  databases over JPA
- `Client`: Client project, making requests over Retrofit
- `db.sql`: Database schema and initial data
- `postman.json`: Can be imported into Postman to more easily test the API
