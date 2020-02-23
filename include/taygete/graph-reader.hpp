//
// @author      : Ruan E. Formigoni (ruanformigoni@gmail.com)
// @file        : graph-reader
// @created     : Thursday Jan 16, 2020 06:26:53 -03
//

#pragma once

#include <lorina/lorina.hpp>
#include <optional>
#include <map>
#include <iostream> // TODO remove

namespace taygete::graph::reader
{


template<typename F1>
class Reader : private lorina::verilog_reader
{
  private:
    mutable F1 callback;
    mutable int64_t base;
    mutable std::map<std::string,int64_t> ids;
  public:
  // Constructors
    template<typename T>
    Reader(T&& input, F1 callback);
  private:
  // Private Methods
    // Modifiers
    virtual void on_module_header( const std::string& module_name,
      const std::vector<std::string>& inouts ) const noexcept override final;
    virtual void on_assign( const std::string& lhs,
        const std::pair<std::string, bool>& rhs ) const noexcept override final;
    virtual void on_and( const std::string& lhs,
      const std::pair<std::string, bool>& op1,
      const std::pair<std::string, bool>& op2 ) const noexcept override final;
    virtual void on_nand( const std::string& lhs,
      const std::pair<std::string, bool>& op1,
      const std::pair<std::string, bool>& op2 ) const noexcept override final;
    virtual void on_or( const std::string& lhs,
      const std::pair<std::string, bool>& op1,
      const std::pair<std::string, bool>& op2 ) const noexcept override final;
    virtual void on_nor( const std::string& lhs,
      const std::pair<std::string, bool>& op1,
      const std::pair<std::string, bool>& op2 ) const noexcept override final;
    virtual void on_xor( const std::string& lhs,
      const std::pair<std::string, bool>& op1,
      const std::pair<std::string, bool>& op2 ) const noexcept override final;
    virtual void on_xnor( const std::string& lhs,
      const std::pair<std::string, bool>& op1,
      const std::pair<std::string, bool>& op2 ) const noexcept override final;
    void update( const std::string& lhs,
      const std::pair<std::string, bool>& op1,
      const std::pair<std::string, bool>& op2 ) const noexcept;
    void update( const std::string& lhs,
      const std::pair<std::string, bool>& rhs ) const noexcept;
};

//
// Constructors
//
template<typename F1>
template<typename T>
Reader<F1>::Reader(T&& input, F1 callback)
  : callback(callback)
  , base(0)
{

  auto const op {lorina::read_verilog(input, *this)};

  if( !(op == lorina::return_code::success) )
  {
    std::cout << "\033[91;1m * \033[mParsing error!" << std::endl;
  }
}

//
// Modifiers
//
template<typename F1>
void Reader<F1>::on_module_header( const std::string& module_name,
    const std::vector<std::string>& inouts ) const noexcept
{
  std::cout << "Module: " << module_name << std::endl;
}

template<typename F1>
void Reader<F1>::on_assign( const std::string& lhs,
    const std::pair<std::string, bool>& rhs ) const noexcept
{
  this->update(lhs, rhs);
}

template<typename F1>
void Reader<F1>::on_and( const std::string& lhs,
  const std::pair<std::string, bool>& op1,
  const std::pair<std::string, bool>& op2 ) const noexcept
{
  this->update(lhs, op1, op2);
}

template<typename F1>
void Reader<F1>::on_nand( const std::string& lhs,
  const std::pair<std::string, bool>& op1,
  const std::pair<std::string, bool>& op2 ) const noexcept
{
  this->update(lhs, op1, op2);
}

template<typename F1>
void Reader<F1>::on_or( const std::string& lhs,
  const std::pair<std::string, bool>& op1,
  const std::pair<std::string, bool>& op2 ) const noexcept
{
  this->update(lhs, op1, op2);
}

template<typename F1>
void Reader<F1>::on_nor( const std::string& lhs,
  const std::pair<std::string, bool>& op1,
  const std::pair<std::string, bool>& op2 ) const noexcept
{
  this->update(lhs, op1, op2);
}

template<typename F1>
void Reader<F1>::on_xor( const std::string& lhs,
  const std::pair<std::string, bool>& op1,
  const std::pair<std::string, bool>& op2 ) const noexcept
{
  this->update(lhs, op1, op2);
}

template<typename F1>
void Reader<F1>::on_xnor( const std::string& lhs,
  const std::pair<std::string, bool>& op1,
  const std::pair<std::string, bool>& op2 ) const noexcept
{
  this->update(lhs, op1, op2);
}

template<typename F1>
void Reader<F1>::update( const std::string& lhs,
  const std::pair<std::string, bool>& op1,
  const std::pair<std::string, bool>& op2 ) const noexcept
{
  if( ! this->ids.contains(op1.first) ) this->ids[op1.first] = this->base++;
  if( ! this->ids.contains(op2.first) ) this->ids[op2.first] = this->base++;
  if( ! this->ids.contains(lhs) ) this->ids[lhs] = this->base++;
  this->callback(this->ids[op1.first], this->ids[lhs]);
  this->callback(this->ids[op2.first], this->ids[lhs]);
}

template<typename F1>
void Reader<F1>::update( const std::string& lhs,
  const std::pair<std::string, bool>& rhs ) const noexcept
{
  if( ! this->ids.contains(lhs) ) this->ids[lhs] = this->base++;
  if( ! this->ids.contains(rhs.first) ) this->ids[rhs.first] = this->base++;
  this->callback(this->ids[rhs.first], this->ids[lhs]);
}

} // namespace taygete::graph::reader
