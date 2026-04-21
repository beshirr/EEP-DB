#pragma once

#include "../config.h"

class BufferPoolManager;
class Page;

/*
 * PageGuard
 * Shared RAII ownership for pinned pages.
 * Non-copyable, movable.
 * */
class PageGuard {
public:
    PageGuard() = default;
    PageGuard(BufferPoolManager* bpm, Page* page) noexcept;

    virtual ~PageGuard();

    // non-copyable
    PageGuard(const PageGuard&) = delete;
    PageGuard& operator=(const PageGuard&) = delete;

    // movable
    PageGuard(PageGuard&& other) noexcept;
    PageGuard& operator=(PageGuard&& other) noexcept;

    [[nodiscard]] bool IsValid() const noexcept;
    [[nodiscard]] page_id_t GetPageId() const noexcept;

protected:
    virtual bool IsDirtyOnDrop() const noexcept = 0;
    void Drop() noexcept;

protected:
    BufferPoolManager* bpm_ = nullptr;
    Page* page_ = nullptr;
};


/*
 * ReadPageGuard
 * Read-only access. */
class ReadPageGuard final : public PageGuard {
public:
    ReadPageGuard() = default;
    ReadPageGuard(BufferPoolManager* bpm, Page* page) noexcept;

    [[nodiscard]] const char* GetData() const noexcept;

protected:
    bool IsDirtyOnDrop() const noexcept override { return false; }
};


/*
 * WritePageGuard
 * Writable access.
 * Automatically marks dirty on destruction. */
class WritePageGuard final : public PageGuard {
public:
    WritePageGuard() = default;
    WritePageGuard(BufferPoolManager* bpm, Page* page) noexcept;

    [[nodiscard]] char* GetData() noexcept;
    [[nodiscard]] const char* GetData() const noexcept;

protected:
    bool IsDirtyOnDrop() const noexcept override { return true; }
};