const { ethers } = require("ethers");
const fs = require("fs");

async function main() {
  const provider = new ethers.providers.JsonRpcProvider(
    "HTTP://127.0.0.1:7545"
  );

  const wallet = new ethers.Wallet(
    "d1beb2a26585277aacabb8361c166b85a8c876b7ab0de55ae83574c49830549e",
    provider
  );

  const abi = fs.readFileSync("./SimpleStorage_sol_SimpleStorage.abi", "utf8");
  const binary = fs.readFileSync(
    "./SimpleStorage_sol_SimpleStorage.bin",
    "utf8"
  );

  const contractFactory = new ethers.ContractFactory(abi, binary, wallet);
  console.log("Deploying, please wait...");
  const contract = await contractFactory.deploy();
  const deploymentRecepit = await contract.deployTransaction.wait(1);
  console.log(`Contract deployed to ${contract.address}`);

  let currentFavoriteNumber = await contract.retrieve();
  console.log(`Current Favorite Number: ${currentFavoriteNumber}`);
  console.log("Updating favorite number...");
  const transactionResponse = await contract.store(7);
  const transactionRecepit = await transactionResponse.wait(1);
  currentFavoriteNumber = await contract.retrieve();
  console.log(`New Favorite Number is ${currentFavoriteNumber}`);
}

main()
  .then(() => process.exit(0))
  .catch((error) => {
    console.log(error);
    process.exit(1);
  });
