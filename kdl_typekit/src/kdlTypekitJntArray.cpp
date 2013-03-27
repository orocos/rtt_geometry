#include "kdlTypekit.hpp"

namespace KDL{
  using namespace std;
  using namespace RTT;


    double& get_item(JntArray& v, int index)
    {
        if (index >= (int) (v.rows()) || index < 0)
            return RTT::internal::NA<double&>::na();
        return v(index);
    }

    double get_item_copy(const JntArray& v, int index)
    {
        if (index >= (int) (v.rows()) || index < 0)
            return RTT::internal::NA<double>::na();
        return v(index);
    }


    int get_size(const JntArray& v)
    {
        return v.rows();
    }

    struct JntArrayTypeInfo : public types::TemplateTypeInfo<JntArray,true>
    {
        JntArrayTypeInfo():TemplateTypeInfo<JntArray, true >("KDL.JntArray")
        {
        };
        
        bool resize(base::DataSourceBase::shared_ptr arg, int size) const
        {
            if (arg->isAssignable()) {
                 RTT::internal::AssignableDataSource<JntArray>::shared_ptr asarg = RTT::internal::AssignableDataSource<JntArray>::narrow( arg.get() );
                asarg->set().resize( size );
                asarg->updated();
                return true;
            }
            return false;
        }

        virtual std::vector<std::string> getMemberNames() const {
            // only discover the parts of this struct:
            std::vector<std::string> result;
            result.push_back("size");
            result.push_back("capacity");
            return result;
        }

        base::DataSourceBase::shared_ptr getMember(base::DataSourceBase::shared_ptr item, const std::string& name) const {
            // the only thing we do is to check for an integer in name, otherwise, assume a part (size) is accessed:
            try {
                unsigned int indx = boost::lexical_cast<unsigned int>(name);
                // @todo could also return a direct reference to item indx using another DS type that respects updated().
                return getMember( item, new RTT::internal::ConstantDataSource<int>(indx));
            } catch(...) {}

            return getMember( item, new RTT::internal::ConstantDataSource<std::string>(name) );
        }

        base::DataSourceBase::shared_ptr getMember(base::DataSourceBase::shared_ptr item,
                                                   base::DataSourceBase::shared_ptr id) const {
            // discover if user gave us a part name or index:
             RTT::internal::DataSource<int>::shared_ptr id_indx = RTT::internal::DataSource<int>::narrow( RTT::internal::DataSourceTypeInfo<int>::getTypeInfo()->convert(id).get() );
             RTT::internal::DataSource<string>::shared_ptr id_name = RTT::internal::DataSource<string>::narrow( id.get() );
            if ( id_name ) {
                if ( id_name->get() == "size" || id_name->get() == "capacity") {
                    try {
                        return RTT::internal::newFunctorDataSource(&get_size, RTT::internal::GenerateDataSource()(item.get()) );
                    } catch(...) {}
                }
            }

            if ( id_indx ) {
                try {
                    if ( item->isAssignable() )
                        return RTT::internal::newFunctorDataSource(&get_item, RTT::internal::GenerateDataSource()(item.get(), id_indx.get() ) );
                    else
                        return RTT::internal::newFunctorDataSource(&get_item_copy, RTT::internal::GenerateDataSource()(item.get(), id_indx.get() ) );
                } catch(...) {}
            }
            if (id_name) {
                log(Error) << "JntArrayTypeInfo: No such member : " << id_name->get() << endlog();
            }
            if (id_indx) {
                log(Error) << "JntArrayTypeInfo: Invalid index : " << id_indx->get() <<":"<< id_indx->getTypeName() << endlog();
            }
            if ( !id_name && ! id_indx)
                log(Error) << "JntArrayTypeInfo: Not a member or index : " << id <<":"<< id->getTypeName() << endlog();
            return base::DataSourceBase::shared_ptr();
        }

    };
    void loadJntArrayTypes(){
        RTT::types::Types()->addType( new JntArrayTypeInfo() );
        RTT::types::Types()->addType( new SequenceTypeInfo<std::vector< JntArray > >("KDL.JntArray[]") );
  };
}  
