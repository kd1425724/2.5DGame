#pragma once
#include <functional>

using namespace std;

enum FeedState
{
    NoFeed,
    FeedIn,
    FeedOut
};

class C_Feed
{
public:

    // time...何フレームでフェード処理が終わるか
    void FeedInInit(float time);

    // time...何フレームでフェード処理が終わるか
    // finishpattern...フェード終了後処理
    void FeedOutInit(float time, function<void()> finishpattern);

    void Update();
    void DrawSprite();

    void FeedEnd();

    FeedState GetFeedState() const { return m_state; }

private:

	void Release();
    // ===== コールバック =====
    function<void()> m_finishpattern = nullptr;

    // ===== 状態 =====
    FeedState m_state = NoFeed;

    float m_alpha = 0.0f;

    // 減少スピード
    float m_delta = 0.0f;

    // フェード中フラグ
    bool m_feedflg = false;

    Math::Matrix m_mat = Math::Matrix::Identity;

private:
    C_Feed() {}
    ~C_Feed() { Release(); }

public:
    static C_Feed& GetInstans()
    {
        static C_Feed instans;
        return instans;
    }
};

#define FEED C_Feed::GetInstans()