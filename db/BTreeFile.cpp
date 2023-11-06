#include <db/BTreeFile.h>
#include <db/Database.h>
#include <cassert>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

using namespace db;

// TODO pa2.2: implement
BTreeLeafPage *BTreeFile::findLeafPage(TransactionId tid, PagesMap &dirtypages, BTreePageId *pid, Permissions perm,
                                       const Field *f) {
//    // Assuming you have a method to fetch the page by page id
//    Page* page = this->getPage(tid, dirtypages, pid, perm);
//
//    while (pid->getType() != BTreePageType::LEAF) {
//        // Assuming you have a method to get an iterator over children of the page
//        auto children = static_cast<BTreeInternalPage*>(page)->begin();
//
//        // If there's no search field, we need the leftmost leaf
//        if (f == nullptr) {
//            pid = children.front().getChildId();
//        } else {
//            // Find the child which could contain the field
//            BTreePageId childToFollow;
//            for (const BTreeEntry& entry : children) {
//                if (entry.getKey()->compare(LessThanOrEq, f)) {
//                    childToFollow = entry.getRightChild();
//                } else {
//                    childToFollow = entry.getLeftChild();
//                    break;
//                }
//            }
//            pid = childToFollow;
//        }
//
//        // Fetch the new page using the childToFollow id
//        page = this->getPage(tid, pid, perm);
//    }
//
//    // If the loop exits, 'page' must be the BTreeLeafPage we are looking for
//    return static_cast<BTreeLeafPage*>(page);
}

// TODO pa2.3: implement
BTreeLeafPage *BTreeFile::splitLeafPage(TransactionId tid, PagesMap &dirtypages, BTreeLeafPage *page, const Field *field) {
//    // Create new right leaf page
//    BTreeLeafPage *rightPage = static_cast<BTreeLeafPage *>(getEmptyPage(tid, BTreePageId::LEAF));
//
//    // Split the full leaf page, moving half the entries to the new page
//    page->moveHalfTuplesTo(rightPage);
//
//    // Update sibling pointers
//    rightPage->setRightSiblingId(page->getRightSiblingId());
//    rightPage->setLeftSiblingId(page->getId());
//    page->setRightSiblingId(rightPage->getId());
//
//    // Insert the new entry into the parent
//    Field middleKey = rightPage->iterator().peekNext().getField(keyField);
//    BTreeInternalPage *parentPage = getParentWithEmptySlots(tid, dirtypages, page->getParentId(), &middleKey);
//    parentPage->insertEntry(new BTreeEntry(middleKey, page->getId(), rightPage->getId()));
//
//    // Update parent pointers for both left and right pages
//    page->setParentId(parentPage->getId());
//    rightPage->setParentId(parentPage->getId());
//
//    // Mark all involved pages as dirty
//    dirtypages.insert(page);
//    dirtypages.insert(parentPage);
//
//    // Determine which page to return
//    if (field != nullptr && field->compare(middleKey) >= 0) {
//        // If the field is greater than or equal to the middle key, return the right page.
//        return rightPage;
//    } else {
//        // Otherwise, return the left page.
//        return page;
//    }
}

BTreeInternalPage *BTreeFile::splitInternalPage(TransactionId tid, PagesMap &dirtypages, BTreeInternalPage *page,
                                                Field *field) {
    // TODO pa2.3: implement
    return nullptr;
}

void BTreeFile::stealFromLeafPage(BTreeLeafPage *page, BTreeLeafPage *sibling, BTreeInternalPage *parent,
                                  BTreeEntry *entry, bool isRightSibling) {
    // TODO pa2.4: implement (BONUS)
}

void BTreeFile::stealFromLeftInternalPage(TransactionId tid, PagesMap &dirtypages, BTreeInternalPage *page,
                                          BTreeInternalPage *leftSibling, BTreeInternalPage *parent,
                                          BTreeEntry *parentEntry) {
    // TODO pa2.4: implement (BONUS)
}

void BTreeFile::stealFromRightInternalPage(TransactionId tid, PagesMap &dirtypages, BTreeInternalPage *page,
                                           BTreeInternalPage *rightSibling, BTreeInternalPage *parent,
                                           BTreeEntry *parentEntry) {
    // TODO pa2.4: implement (BONUS)
}

void BTreeFile::mergeLeafPages(TransactionId tid, PagesMap &dirtypages, BTreeLeafPage *leftPage,
                               BTreeLeafPage *rightPage, BTreeInternalPage *parent, BTreeEntry *parentEntry) {
    // TODO pa2.4: implement (BONUS)
}

void BTreeFile::mergeInternalPages(TransactionId tid, PagesMap &dirtypages, BTreeInternalPage *leftPage,
                                   BTreeInternalPage *rightPage, BTreeInternalPage *parent, BTreeEntry *parentEntry) {
    // TODO pa2.4: implement (BONUS)
}

BTreeFile::BTreeFile(const char *fname, int key, const TupleDesc &td) : keyField(key), td(td) {
    fd = open(fname, O_RDWR | O_CREAT | O_APPEND | O_TRUNC, 0644);
    if (fd == -1) {
        throw std::runtime_error("open");
    }
    tableid = std::hash<std::string>{}(fname);
}