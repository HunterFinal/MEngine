/**
 * @file AbstractDelegate.h
 * @author MAI ZHICONG
 * @brief Base class of singlecast delegate
 * @version 0.1
 * @date 2025-10-14
 * 
 * @copyright Copyright (c) 2025~2025 MAI ZHICONG
 * 
 */

#pragma once

#ifndef _ME_ABSTRACT_DELEGATE_
#define _ME_ABSTRACT_DELEGATE_

#include "CoreDefines.h"
#include "Allocation/Allocator.h"
#include "Delegates/IDelegateInterface.h"
#include "Math/MEngineMathUtility.h"

namespace MEngine
{

namespace Core
{
  /**
   * @brief Base of singlecast delegate
   * 
   *        Non thread-safe,use it without multithreaded programming
   * 
   *        シングルキャストデリゲートの基底クラス
   * 
   *        -----------------------------------------------------------
   * 
   *        ※スレッドセーフではない。マルチスレッドプログラミングに使わない
   * 
   *        -----------------------------------------------------------
   */
  class MAbstractDelegate
  {
    #pragma region Friend class
    template<typename>
    friend class MStaticFunctionDelegateInstance;

    template<bool, typename, typename>
    friend class MClassMethodDelegateInstance;

    friend class MAbstractMulticastDelegate;
    #pragma endregion Friend class

    TYPEDEF(DefaultAllocator<IDelegateInterface>, DelegateAllocator);
    
    protected:
      /**
       * @brief Default constructor.Access only in derived class
       * 
       *        デフォルトコンストラクタ。自身と派生クラスにしかアクセスできない
       */
      MAbstractDelegate() = default;
      public:

      /**
       * @brief Destructor
       * 
       *        デストラクタ
       */
      CORE_API virtual ~MAbstractDelegate();

      /**
       * @brief Move constructor
       * 
       *        ムーブコンストラクタ
       */
      MAbstractDelegate(IN MAbstractDelegate&& Other) noexcept = default;

      /**
       * @brief Move assignment
       * 
       *        ムーブアサインメント
       */
      MAbstractDelegate& operator=(IN MAbstractDelegate&& Other) noexcept = default;

      /**
       * @brief Check if two delegates have the same handle
       * 
       *        二つのデリゲートが同じハンドルを持っているかを確認する
       * 
       * @param Lhs The first delegate
       * @param Rhs The second delegate
       * @return true if two delegate's instances have same handle, false otherwise
       * 
       *         同じハンドルを持っていればtrue、それ以外の状況はfalse
       */
      CORE_API friend bool operator==(IN const MAbstractDelegate& Lhs, IN const MAbstractDelegate& Rhs);
      CORE_API friend bool operator!=(IN const MAbstractDelegate& Lhs, IN const MAbstractDelegate& Rhs);
      
      /**
       * @brief Unbind delegate instance
       * 
       *        デリゲートの登録を解除する
       */
      CORE_API void Unbind();

      /**
       * @brief Get instance pointer used by delegate instance as specific <UserClass> type
       * 
       *        デリゲートに登録したユーザー定義クラスインスタントポインタを取得
       * 
       * @tparam UserClass User-defined class
       * 
       *         ユーザー定義クラス
       * 
       * @return User instance pointer as specific type,
       *         nullptr if it doesn't inherit to <UserClass> or doesn't have an instance pointer
       * 
       *         ユーザー定義クラスインスタンスが<UserClass>じゃないもしくは存在しない場合、nullptrを返す
       */
      template<typename UserClass>
      FORCEINLINE UserClass* GetTypedInstancePtr() const;

      /**
       * @brief Check if this delegate is bound to a valid delegate instance
       * 
       *        デリゲートがバインドされている状態を確認する
       * 
       * @return true if bound to a valid delegate instance, false otherwise
       * 
       *         バインドされていたらtrueを返す、それ以外falseを返す
       */
      CORE_API bool IsBound() const;

      /**
       * @brief Check if this delegate has a user instance pointer
       * 
       * @param InstancePtr User instance pointer
       * 
       *        ユーザー定義クラスインスタンスポインタ
       * 
       * @return true if has a valid delegata instance and using a user instance pointer, false otherwise
       * 
       *         有効なデリゲートインスタンスかつユーザー定義クラスインスタンスポインタを持っていればtrueを返す、それ以外falseを返す
       */
      CORE_API bool IsBoundToInstance(IN const void* InstancePtr) const;

      /**
       * @brief Get handle that is keeping by delegate instance
       * 
       *        ハンドルを返す
       * 
       * @return handle of delegate instance if delegate instance is valid, invalid handle otherwise
       * 
       *         デリゲートインスタントが有効だったら有効なハンドルを返す、それ以外無効なハンドルを返す
       */
      CORE_API MDelegateHandle GetHandle() const;
      
    protected:
      /**
       * @brief Create a delegate instance.Access only in a derived class.
       *        
       *        デリゲートインスタントを作る。自身もしくは派生クラスしかアクセスできない。
       * 
       * @tparam DelegateInstanceType Delegate instance type that wants to create
       * 
       *         デリゲートインスタントの型
       * 
       * @tparam InstanceConstrucParamTypes Parameter types to construct delegate instance
       * 
       *         デリゲートインスタントを作るための可変長引数の型 
       * 
       * @param Params Parameters use to construct delegate instance
       * 
       *        デリゲートインスタントを作るための可変長引数
       */
      template<typename DelegateType, typename... InstanceConstrucParamTypes>
      FORCEINLINE void CreateDelegateInstance(IN InstanceConstrucParamTypes... Params);
      
      /**
       * @brief Get delegate instance interface.Access only in a derived class.
       * 
       *        デリゲートインスタントインタフェースを取得。自身もしくは派生クラスしかアクセスできない。
       * 
       * @return Delegate instance interface, return nullptr if is not allocated
       * 
       *         デリゲートインスタントインタフェース
       * 
       * @note   インスタントが作られていないとnullptrを返す
       */
      FORCEINLINE IDelegateInterface* GetDelegateInterfaceInternal();

      /**
       * @brief Get delegate instance interface.Access only in a derived class.
       * 
       *        デリゲートインスタントインタフェースを取得。自身もしくは派生クラスしかアクセスできない。
       * 
       * @return Delegate instance interface, return nullptr if is not allocated
       * 
       *         デリゲートインスタントインタフェース
       * 
       * @note   インスタントが作られていないとnullptrを返す
       */
      FORCEINLINE const IDelegateInterface* GetDelegateInterfaceInternal() const;

    private:
      /**
       * @brief Allocate memory for delegate instance
       * 
       *        デリゲートインスタントメモリ確保
       * 
       * @param AllocSize Size(byte) of memory allocation
       * 
       *        確保するメモリのサイズ（バイト単位）
       * 
       * @return Pointer of allocated delegate instance
       * 
       *         確保したメモリの先頭アドレス
       */
      FORCEINLINE void* AllocateInternal(IN SIZE_T AllocSize);

    private:
      DelegateAllocator m_allocator; // Allocator that manage memory of delegate instance

    public:
      /**
       * @breif Uncopyable
       * 
       *        コピー禁止
       */
      MAbstractDelegate(const MAbstractDelegate&) = delete;
      MAbstractDelegate& operator=(const MAbstractDelegate&) = delete;
  };

  template<typename UserClass>
  UserClass* MAbstractDelegate::GetTypedInstancePtr() const
  {
    return dynamic_cast<UserClass*>(m_allocator.GetAllocation());
  }

  template<typename DelegateType, typename... InstanceConstrucParamTypes>
  void MAbstractDelegate::CreateDelegateInstance(IN InstanceConstrucParamTypes... Params)
  {
    const IDelegateInterface* delegateInterface = m_allocator.GetAllocation();

    // placement new must call destructor manually
    // プレイスメントnewで作ったインスタントは手動でデストラクタを呼ぶ
    if(delegateInterface != nullptr)
    {
      delegateInterface->~IDelegateInterface();
    }

    new(AllocateInternal(sizeof(DelegateType))) DelegateType(Params...);
  }

  IDelegateInterface* MAbstractDelegate::GetDelegateInterfaceInternal()
  {
    return const_cast<IDelegateInterface*>(static_cast<const MAbstractDelegate*>(this)->GetDelegateInterfaceInternal());
  }

  const IDelegateInterface* MAbstractDelegate::GetDelegateInterfaceInternal() const
  {
    return m_allocator.GetAllocation();
  }

  void* MAbstractDelegate::AllocateInternal(IN SIZE_T AllocSize)
  {
    // TODO 16 is a magic number of block size of each delegate instance
    // マジックナンバー16はデリゲートインスタントのメモリを確保するメモリブロックのサイズ
    const SIZE_T blockSizePerInst = static_cast<SIZE_T>(16);
    const SIZE_T delegateInstanceElementNum = MMath::DivideCeil(AllocSize, blockSizePerInst);
    m_allocator.Allocate(delegateInstanceElementNum, blockSizePerInst);

    return reinterpret_cast<void*>(m_allocator.GetAllocation());
  }
} // namespace MEngine::Core

} // namespace MEngine

#endif // _ME_ABSTRACT_DELEGATE_