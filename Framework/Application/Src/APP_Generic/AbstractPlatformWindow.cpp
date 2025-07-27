#include "APP_Generic/AbstractApplicationWindow.h"

namespace MEngine
{

namespace Application
{
  MAbstractApplicationWindow::MAbstractApplicationWindow()
    : m_definition{}
  { }

  MAbstractApplicationWindow::~MAbstractApplicationWindow() = default;

  MAbstractApplicationWindow::MAbstractApplicationWindow(IN MAbstractApplicationWindow&& Other) noexcept
  {
    m_definition = std::move(Other.m_definition);
    Other.m_definition = {};
  }

  MAbstractApplicationWindow& MAbstractApplicationWindow::operator=(IN MAbstractApplicationWindow&& Other) noexcept
  {
    if (this != &Other)
    {
      m_definition = std::move(Other.m_definition);
      Other.m_definition = {};
    }

    return *this;
  }

} // namespace MEngine::Application

} // namespace MEngine