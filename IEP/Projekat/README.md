# IEP project

This project is about building an API which handles various aspects of an
e-store, using Flask for the backend, SQLAlchemy for the database, Redis for
queueing, packaging all of that in Docker containers and orchestrating them with
Docker Swarm. It comes with automated tests that ensure it is working correctly.
You can read the [project specification](https://web.archive.org/web/20230604002730/https://rti.etf.bg.ac.rs/rti/si3iep/projekti/IEP_PROJEKAT_2022.pdf)
(in Serbian) for more details.

## Structure
- `authentication`: Container handling authentication for the entire e-store
- `admin`: Container handling product and category statistics
- `customer`: Container handling customer orders and search
- `warehouse`: Container handling updates to the store's warehouses
- `daemon`: Container taking orders from customers from Redis and fulfilling
  them
- `shared`: Shared logic between containers
- `krastavac`/`paradajz`: Containers creating the initial database tables
- `tests`: Automated tests for the APIs
