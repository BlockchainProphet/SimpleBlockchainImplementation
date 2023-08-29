#include "Blockchain.h"
#include <iostream>

Blockchain::Blockchain() {
    std::vector<Transaction> emptyTransactions;  // Empty list for genesis block
    chain.emplace_back(emptyTransactions, "0", 2);  // Genesis Block
}

void Blockchain::createTransaction(Transaction transaction) {
    pendingTransactions.push_back(transaction);
}

void Blockchain::minePendingTransactions() {
    Block newBlock(pendingTransactions, chain.back().blockHash, 2);
    chain.push_back(newBlock);
    pendingTransactions.clear();  // Clear pending transactions
}

bool Blockchain::isBlockHashValid(const Block& block) {
    return block.blockHash == block.generateHash();
}

bool Blockchain::isTransactionValid(const Transaction& tx) {
    return tx.amount > 0;
}

bool Blockchain::isChainValid() {
    for (int i = 1; i < chain.size(); ++i) {
        Block currBlock = chain[i];
        Block prevBlock = chain[i - 1];

        if (!isBlockHashValid(currBlock)) {
            return false;
        }

        if (currBlock.prevHash != prevBlock.blockHash) {
            return false;
        }

        for (const auto& tx : currBlock.transactions) {
            if (!isTransactionValid(tx)) {
                return false;
            }
        }
    }
    return true;
}

void Blockchain::printChain() {
    for (const auto& block : chain) {
        std::cout << "Block Timestamp: " << block.timestamp << std::endl;
        std::cout << "Previous Hash: " << block.prevHash << std::endl;
        std::cout << "Block Hash: " << block.blockHash << std::endl;
        std::cout << "Transactions:" << std::endl;
        for (const auto& tx : block.transactions) {
            std::cout << "  Sender: " << tx.sender << " Receiver: " << tx.receiver << " Amount: " << tx.amount << std::endl;
        }
        std::cout << std::endl;
    }
}