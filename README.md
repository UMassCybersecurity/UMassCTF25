## TODO Finish

# CTF Template Repository 

## Our Environment Setup  
We have development and production environments (two CTF environments) which are managed from the dev and prod branches. You will **NOT** be able to promote a challenge to production until it has passed E2E testing and been tested in the dev environment. 🤓

## How to Make a Challenge
1. Create a branch for your challenge named *category*/*challenge name*.
2. Create a new directory in the appropriate category for your challenge.
    - Use the following format (challenges/[category]/[challenge name])
    - Each challenge should have the following things at the top level:
        - An optional static folder with downloadable assets.
        - If dynamic: A Dockerfile with the EXPOSE tag or a docker-compose.yaml file.
        - info.yaml (see [info.yaml](./refs/info.yaml) for a basic reference or [full-info.yaml](./refs/full-info.yaml) for a full one)
3. Create a PR to merge into the dev branch.
4. Test your challenges in the CTFd dev environment. Create any follow up PRs as necessary to make edits to your challenge. 
5. Create a PR to promote your challenge to the prod branch.


## End to End Testing (E2E)
Our E2E tests will validate the following:
- The Docker container builds 
- info.yaml contains all required fields 

## Additional References
Docker File
- https://docs.docker.com/reference/dockerfile/
- https://medium.com/@anshita.bhasin/a-step-by-step-guide-to-create-dockerfile-9e3744d38d11
