<p align="center">
  <img src="UMassCybersec.png" width="45%" style="margin-right: 15px;" />
  <img src="CTFd.png" width="45%" />
</p>

---
<p align="center">
  <h3 align="center">
    <a href="https://ctf.umasscybersec.org/"> 🚩 UMass CTF 2025 </a> 
  </h3>
  <h3 align="center">
    🕠 April 18th 2 PM - 20th 8 PM 
  </h3>
</p>

---
* [🚩 What is UMassCTFd?](#-UMassCtfd)
    + [📖 Overview](#-overview)
    + [🏗️ Architecture](#-architecture)
* [🚀 Quickstart - *for challenge authors*](#-quickstart)
    + [💻 Writing Challenges](#-writing-challs)
    + [🎉 Deploying Challenges](#-deploying-challs)
    + [ 🎮 Playtesting Challenges](#-deploying-challs)
    + [✏️ Editing Challenges](#-editing-challs)
* [🛠️  Installation & Deployment - *for infra team*](#-deploy)
    + [1️⃣ Provision Cloud or On-Prem Services](#-provision)
    + [2️⃣  Setup CTFd](#-setup-ctfd)
    + [ 3️⃣ Configure Github Repo & Actions](#-github-repo)
* Custom Configuration
---

## 🚩 What is UMassCTFd?  

UMassCTFd is an automated challenge + CTFd deployer used to provision and manage UMass Cybersecurity Club's CTFs and internal training platforms. 

###  📖 Overview

**Challenge Categories:**

Each challenge category will have its own subdirectory under `/challenges`. All challenge directories must be placed in a subdirectory under `/challenges/${CATEGORY}/`
```
# Example Structure

/challenges/
 ├── crypto/
 │    ├── challenge1/
 │    ├── challenge2/
 ├── web/
 │    ├── challenge1/
 │    ├── challenge2/
```

The default challenge categories are:
- crypto 
- forensics 
- hardware 
- misc 
- pwn 
- rev
- web 
- OSINT

To add a new category, you can just create a new subdirectory under `/challenges`.

**Challenge Contents:**  
We support automated deployment of challenges with static assets, interactive Docker containers, both or neither, and even more complicated setups (via Docker Compose)!  

**Environments:**  
We have a "dev" and "prod" environment, each with an associated Github branch.  
As per best GitOps practices 🤓, you should play test your challenge in the dev environment first before promoting it to prod.   

> [!NOTE]  
> Our prod environment will not be set up until ~1 week before the CTF to reduce infrastructure costs.

###  🏗️ Architecture

This repo is the *SINGLE SOURCE OF TRUTH*. Every challenge's information on CTFd (ex. description, points, etc.) & source code will live here. 

> [!WARNING]  
> Making manual changes in CTFd *WILL* get overriden by our CI/CD pipelines. Deploying and updating challenges should only be done through this repo. 
> We plan to add support for updating/syncing challenge information in CTFd as well in the near future.  

Both CTFd and all challenges are hosted on GCP. The diagram below gives a high-level overview of how our infrastructure works:  

## 🚀 Quickstart 

### 💻 Writing Challenges

> [!IMPORTANT]
> Flag Format: `UMASS{FLAG}`

1. **Create a new directory** for your challenge within the appropriate category directory:  
   `/challenges/${CHALLENGE_CATEGORY}/${CHALLENGE_NAME}`  

   > Ensure your challenge name follows this regex pattern:  
   > `^[A-Za-z][A-Za-z0-9-]*$`

2. **Each challenge directory must include the following files:**  
   - **Required:**  
     - `info.yaml`: Contains the challenge metadata (used for CTFd entry).   
   - **Optional (depending on challenge type):**  
     - If the challenge includes **static downloadable assets** (e.g., images, source code files), create a `static` subdirectory to store them.  
     - If the challenge requires **running services** (e.g., a website, interactive script), include a `docker-compose.yaml` file.
       - <details>
         <summary>Need a <u>separate instance</u> for each connection?</summary>
         
         If your service should **start a fresh instance per user connection** (e.g., for binary exploitation or sandboxed environments), use `ynetd` in your `Dockerfile`.  
         `ynetd` ensures each connection gets its own isolated process without reusing state from previous users.
         
         Example:
         ```dockerfile
         FROM debian:latest
         RUN apt update && apt install -y ynetd
         COPY challenge_binary /challenge
         CMD ["ynetd", "-p", "1337", "-u", "nobody", "--", "/challenge"]
         ```
         </details>
       - <details>
         <summary>Running <u>multiple services?</u></summary>
         
         If your challenge requires **multiple services** (e.g., a database, chat bot, API, etc.), you can define them in your `docker-compose.yaml` file.  
         This allows you to specify how different containers interact with each other.
         
         Example:
         ```yaml
         version: "3"
         services:
           web:
             build: ./web
             ports:
               - "8080:80"
           db:
             image: mysql:latest
             environment:
               MYSQL_ROOT_PASSWORD: root
               MYSQL_DATABASE: challenge_db
           bot:
             build: ./bot
             depends_on:
               - db
         ```
         In this example:
         - `web` is a service running a website.
         - `db` is a MySQL database.
         - `bot` is a chatbot that depends on the database.
         
         You can add more services as needed and configure them accordingly in `docker-compose.yaml`.
        </details>
---

**Writing Dockerfiles** 

<details> 
    <summary> if each user needs a new interactive session: </summary>
</details>

<details> 
    <summary> if you need extra services (web): </summary>
</details>

**Choosing a Public Port**



#TODO: have the chat reword this

#TODO fix this up, go over info.yaml  
    Create a new directory in the appropriate category for your challenge.
        Use the following format (challenges/[category]/[challenge name])
            Please make sure the challenge name does not contain any underscores, capital letters, or special characters.
        Each challenge should have the following things at the top level:
            an optional static folder with downloadable assets
            a Dockerfile/docker-compose.yaml and a config.env if dynamic (see this config.env for reference)
            info.yaml (see this info.yaml for reference)
    Create a PR to merge into the dev branch.
    Test your challenges in the CTFd dev environment. Create any follow up PRs as necessary to make edits to your challenge.
    Create a PR to promote your challenge to the prod branch.


- Use base image of alpine wnv possible (ex-alpine) # link video of how to make docker images smaller (provide the tips and tricks here?) -> checklist dropdown?  

Exposing ports: 

Pwn: 30000-31000
Crypto: 40000-41000
Web: 50000-51000
Other: 60000-61000




for Web: 


for Pwn: 




### 🎉 Deploying Challenges

**End to End Tests**
Before deploying your challenge, you must validate that the automatic end to end(E2E) tests have passed. 
#TODO: say what we test, include screenshot of green check mark, include instructions for troubleshooting if they fail 

**Merging**
#TODO PR reivew (ping someone)? 
#TODO: also put don't edit main branch and stuff in here 


to dev 
to prod 

### 🎮 Playtesting Challenges
#TODO: put connection info in here 

### ✏️ Editing Challenges

## 🛠️  Installation & Deployment

### 1. Provision Cloud or On-Prem Services 
Challenges can be deployed on virtual machines hosted on a cloud platform or on-prem servers.  

<details>
  <summary><h4>GCP</h4></summary>

**1. Create a GCP project**  
```sh
# TODO: replace ${PROJECT_NAME} with your GCP project name 

gcloud projects create PROJECT_ID --name="${PROJECT_NAME}"
```

**2. Authenticate with the GCP CLI**  
```sh
gcloud auth login
```
**3. Set GCP CLI project config**  
```sh
# TODO: replace ${PROJECT_ID} with your GCP project ID 

gcloud config set project ${PROJECT_ID}
```

**4. Create a VM for each challenge category**  
```sh
# TODO: replace ${CATEGORY_1} ${CATEGORY_2} ... ${CATEGORY_N} with your challenge categories; replace ${ZONE} and ${MACHINE_TYPE} with your GCP zone and Compute Engine machine type respectively 

for category in ${CATEGORY_1} ${CATEGORY_2} ${CATEGORY_N}; do
  gcloud compute instances create "${category}-challs" --zone=${ZONE} --machine-type=${MACHINE_TYPE}
done

# Example: 
# for category in web pwn misc; do
#   gcloud compute instances create "${category}-challs" --zone=us-east1-b --machine-type=e2-medium
# done
```

**5. Expose ports** #TODO 
add tags w/ above creation command 

they have to be network tags

```sh


Pwn: 30000-31000
Crypto: 40000-41000
Web: 50000-51000
Other: 60000-61000

gcloud compute instances add-tags pwn-crypto-challs --tags=pwn --zone=us-east1-b
gcloud compute instances add-tags pwn-crypto-challs --tags=crypto --zone=us-east1-b
gcloud compute instances add-tags mixed-challs --tags=other --zone-us-east1-b
gcloud compute instances add-tags web-challs --tags=web --zone-us-east1-b


gcloud compute firewall-rules create allow-pwn-port-range \
    --network=default \
    --allow=tcp:30000-31000 \
    --source-ranges=0.0.0.0/0 \
    --target-tags=pwn \
    --direction=INGRESS

gcloud compute firewall-rules create allow-crypto-port-range \
    --network=default \
    --allow=tcp:40000-41000 \
    --source-ranges=0.0.0.0/0 \
    --target-tags=crypto \
    --direction=INGRESS

gcloud compute firewall-rules create allow-web-port-range \
    --network=default \
    --allow=tcp:50000-51000 \
    --source-ranges=0.0.0.0/0 \
    --target-tags=web \
    --direction=INGRESS

gcloud compute firewall-rules create allow-other-port-range \
    --network=default \
    --allow=tcp:60000-61000 \
    --source-ranges=0.0.0.0/0 \
    --target-tags=other \
    --direction=INGRESS
```




**6. Create Public Storage Bucket**

*6a. Create the bucket* 
```
gsutil mb -b on -l us-east1 gs://umassctf25-dev-static-assets/
```

*6b. Make it publically accessible*
```
gsutil iam ch allUsers:objectViewer gs://umassctf25-dev-static-assets/
```

**7. Authenticate to GCP via Workload Identity Federation**

#TODO: check this over
This [repo](https://github.com/google-github-actions/auth) has detailed documentation about Github Action authentication to GCP.

> Woarkload Identity Federation is used to establish a trust delgation relationship between Github Actions workflow invocation and GCP permissions without storing service account keys.
> - Workload Identity Pool: "container" for external identities, groups multiple identity providers (ex. Github) and allows them to assume GCP IAM roles; the Workload Identity Pool will have direct IAM permissions on GCP resources.
> - Workload Identity Provider: specific OIDC identity source (ex. Github) within a Workload Identity Pool 

*6a. Create a Workload Identity Pool*
```sh 
# TODO: replace ${PROJECT_ID} with your value below.

gcloud iam workload-identity-pools create "github" \
  --project="${PROJECT_ID}" \
  --location="global" \
  --display-name="GitHub Actions Pool"
```

*6b. Get full ID of Workload Identity Pool* 
```sh
# TODO: replace ${PROJECT_ID} with your value below.

gcloud iam workload-identity-pools describe "github" \
  --project="${PROJECT_ID}" \
  --location="global" \
  --format="value(name)"

# value should be of format `projects/123456789/locations/global/workloadIdentityPools/github`
```

*6c. Create a Workload Identity Provider in the pool*
```
# TODO: replace ${PROJECT_ID} and ${GITHUB_ORG} with your values below.

gcloud iam workload-identity-pools providers create-oidc "my-repo" \
  --project="${PROJECT_ID}" \
  --location="global" \
  --workload-identity-pool="github" \
  --display-name="My GitHub repo Provider" \
  --attribute-mapping="google.subject=assertion.sub,attribute.actor=assertion.actor,attribute.repository=assertion.repository,attribute.repository_owner=assertion.repository_owner" \
  --attribute-condition="assertion.repository_owner == '${GITHUB_ORG}'" \
  --issuer-uri="https://token.actions.githubusercontent.com"

# Example: 
# gcloud iam workload-identity-pools providers create-oidc "umassctf25" \
#  --location="global" \
#  --workload-identity-pool="github" \
#  --display-name="UMassCTF25 Github Repo" \
#  --attribute-mapping="google.subject=assertion.sub,attribute.actor=assertion.actor,attribute.repository=assertion.repository,attribute.repository_owner=assertion.repository_owner" \
#  --attribute-condition="assertion.repository_owner == 'UMassCybersecurity'" \
#  --issuer-uri="https://token.actions.githubusercontent.com"
```

*6e. Allow authentications from Workload Identity Pool to GCP Compute Engine and Storage Bucket resources*
```
# For Compute Engine 
gcloud projects add-iam-policy-binding "${PROJECT_ID}" \
  --member="principalSet://iam.googleapis.com/${WORKLOAD_IDENTITY_POOL_ID}/attribute.repository/${REPO}" \
  --role="roles/compute.instanceAdmin.v1"

# For Cloud Storage 
gcloud projects add-iam-policy-binding "${PROJECT_ID}" \
  --member="principalSet://iam.googleapis.com/${WORKLOAD_IDENTITY_POOL_ID}/attribute.repository/${REPO}" \
  --role="roles/storage.admin"

# Example 
# For Compute Engine 
gcloud projects add-iam-policy-binding "umassctf25-dev" \
  --member="principalSet://iam.googleapis.com/projects/75881137583/locations/global/workloadIdentityPools/github/attribute.repository/UMassCTF25" \
  --role="roles/compute.instanceAdmin.v1"

# For Cloud Storage 
gcloud projects add-iam-policy-binding "umassctf25-dev" \
  --member="principalSet://iam.googleapis.com/projects/75881137583/locations/global/workloadIdentityPools/github/attribute.repository/UMassCTF25" \
  --role="roles/storage.admin"

gcloud projects add-iam-policy-binding "umassctf25-dev" \
  --member="principalSet://iam.googleapis.com/projects/75881137583/locations/global/workloadIdentityPools/github/attribute.repository/UmassCybersecurity/UMassCTF25" \
  --role="roles/storage.objectAdmin"

```

- also grant the role `iam.serviceAccountUser` to your principle on the default compute engine service account 

</details>

# TEST COMPUTE FIRST to see if the permissions are getting carried over, scp? 

<details>
  <summary><h4>Proxmox</h4></summary>
  This is the hidden content that appears when you click the summary.
</details>

### 2. Set up CTFd

#TODO This article is fucked so just include commands manually lowkey, also create script 

Follow this https://dev.to/roeeyn/how-to-setup-your-ctfd-platform-with-https-and-ssl-3fda article to set up CTFd. It can be hosted on one of the challenge VMs or a seperate VM depending on anticipated traffic.   

Expose HTTP/HTTPs traffic on the VM hosting CTFd. 

### 3. Configure Github Repo &  Actions 

1) Add `WORKLOAD_IDENTITY_PROVIDER_NAME` repo variable; to get value, run 
```
gcloud iam workload-identity-pools providers describe "umassctf25" \
  --location="global" \
  --workload-identity-pool="github" \
  --format="value(name)"

expected format: projects/75881137583/locations/global/workloadIdentityPools/github/providers/umassctf25
```

2) Add `PROJECT_ID` repo variable; to get value #TODO

3) Add "WEB_CHALLS_VM_NAME" "PWN_CRYPTO_CHALLS_VM_NAME" "MIXED_CHALLS_VM_NAME" 
"web-challs"
"mixed-challs"
"pwn-crypto-challs"

4) Add `ZONE`
6) Add `STATIC_ASSETS_BUCKET_NAME`
"umassctf25-dev-static-assets"
---
7) Add `CTFD_URL`


---
#TODO:
- step to install docker on all machines? 
- squash commits
- why isnt [!NOTE] working?
- TODO: fix replacements in the workload identity provider
- make the workloa didentity provider steps a substep
- make sure to mention access in terms of merging, who to ping, etc.
- have the dev environment setup and have IP and password information in this README so people can connect to dev instance
- create GH team with all users?
- The instructions need to be rewritten they are lowkey a mess, need to add variables 
- Create a port tracker file (provide ranges for each category), then expose those ranges : put note that says this will be automatically managed soon 
- automate DNS? and nginx config figure out
- setup bastion host for dev environmnet?
- look into autoscaling for the VMs
- solve scripts
- description for ynetd
- move images to docs folder or smthing
- clean up branches + random folders in this repo, old PRs
- there are some stuff that should be variables in the gh actions
- get rid of old gh pipeline workflow, document how pipeline workflow works 
- get rid of ./examples/test
- do i need region env variable?
- why is it failing with "updating project metadata?"  
- do i need region env variable?  
- do i need region env variable?  
- have docs for both pipelines
- update About github description 
- do i need region env variable?  
- is it failing on other ppls info.yaml being inaccurate too ? 
- fix example info.yamls
- check over ynetd example 
