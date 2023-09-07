#include "txfee_eosio_bios.hpp"

namespace eosio {

void bios::setabi( name account, const std::vector<char>& abi ) {
   abi_hash_table table(get_self(), get_self().value);
   auto itr = table.find( account.value );
   if( itr == table.end() ) {
      table.emplace( account, [&]( auto& row ) {
         row.owner = account;
         row.hash  = sha256(const_cast<char*>(abi.data()), abi.size());
      });
   } else {
      table.modify( itr, same_payer, [&]( auto& row ) {
         row.hash = sha256(const_cast<char*>(abi.data()), abi.size());
      });
   }
}

void bios::onerror( ignore<uint128_t>, ignore<std::vector<char>> ) {
   check( false, "the onerror action cannot be called directly" );
}

void bios::setpriv( name account, uint8_t is_priv ) {
   require_auth( get_self() );
   set_privileged( account, is_priv );
}

void bios::setalimits( name account, int64_t ram_bytes, int64_t net_weight, int64_t cpu_weight ) {
   require_auth( get_self() );
   set_resource_limits( account, ram_bytes, net_weight, cpu_weight );
}

void bios::setprods( std::vector<eosio::producer_key> schedule ) {
   require_auth( get_self() );
   set_proposed_producers( schedule );
}

void bios::setparams( const eosio::blockchain_parameters& params ) {
   require_auth( get_self() );
   set_blockchain_parameters( params );
}

void bios::reqauth( name from ) {
   require_auth( from );
}

void bios::activate( const eosio::checksum256& feature_digest ) {
   require_auth( get_self() );
   preactivate_feature( feature_digest );
}

void bios::reqactivated( const eosio::checksum256& feature_digest ) {
   check( is_feature_activated( feature_digest ), "protocol feature is not activated" );
}

void bios::setfeeparams( uint64_t cpu_fee_scaler, uint64_t free_block_cpu_threshold, uint64_t net_fee_scaler, uint64_t free_block_net_threshold ) {
   require_auth( get_self() );
   set_fee_parameters(cpu_fee_scaler, free_block_cpu_threshold, net_fee_scaler, free_block_net_threshold);
}

void bios::cfgfeelimits( name account, int64_t tx_fee_limit, int64_t account_fee_limit) {
   require_auth( get_self() );
   config_fee_limits(account, tx_fee_limit, account_fee_limit);
}

void bios::setfeelimits( name account, int64_t net_weight_limit, int64_t cpu_weight_limit ) {
   require_auth( get_self() );
   set_fee_limits( account, net_weight_limit, cpu_weight_limit );
}
}