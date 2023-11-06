#include <db/BufferPool.h>
#include <db/Database.h>

using namespace db;

// TODO pa2.1
void BufferPool::evictPage() {
    // simple eviction: remove the first page
    for (auto it = pages.begin(); it != pages.end(); ++it) {
        if (it->second->isDirty()) {
            // If the page is dirty, we flush it, making sure dirty pages are updated on disk
            flushPage(it->first);
        }
        // discard the page
        delete it->second;
        pages.erase(it);
        return;
    }
}

// TODO pa2.1
void BufferPool::flushAllPages() {
    // flush pages one by one
    for (auto &entry : pages) {
        flushPage(entry.first);
    }
}

// TODO pa2.1
void BufferPool::discardPage(const PageId *pid) {
    // find the page through pid
    auto it = pages.find(pid);
    // erase the page
    if (it != pages.end()) {
        delete it->second;
        pages.erase(it);
    }
}

// TODO pa2.1
void BufferPool::flushPage(const PageId *pid) {
    // find the page through pid
    auto it = pages.find(pid);
    // find a dirty page from the begin
    if (it != pages.end() && it->second->isDirty()) {
        // write the page into disk
        Database::getCatalog().getDatabaseFile(pid->getTableId())->writePage(it->second);
        // and mark it as undirty (no value)
        it->second->markDirty(std::nullopt);
    }
}

// TODO pa2.1
void BufferPool::flushPages(const TransactionId &tid) {
    for (auto &entry : pages) {
        if (entry.second->isDirty() == tid) {
            flushPage(entry.first);
        }
    }
}

void BufferPool::insertTuple(const TransactionId &tid, int tableId, Tuple *t) {
    // TODO pa2.3: implement
//    // Logic to determine the appropriate page
//    Page *page = ...; // (omitted)
//    page->insertTuple(*t);
//    page->markDirty(tid); // Mark the page as dirty with the transaction id
//    // Add the page to the buffer pool if it's not already present
//    pages.emplace(&page->getId(), page);
}

void BufferPool::deleteTuple(const TransactionId &tid, Tuple *t) {
    // TODO pa2.3: implement
//    PageId pid = t->getRecordId().getPageId();
//    Page *page = getPage(&pid);
//    page->deleteTuple(*t);
//    page->markDirty(tid); // Mark the page as dirty with the transaction id
}
