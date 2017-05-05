#include "kdlTypekit.hpp"

template class RTT::internal::DataSource< ::KDL::JntArray >;
template class RTT::internal::AssignableDataSource< ::KDL::JntArray >;
template class RTT::internal::ValueDataSource< ::KDL::JntArray >;
template class RTT::internal::ConstantDataSource< ::KDL::JntArray >;
template class RTT::internal::ReferenceDataSource< ::KDL::JntArray >;
template class RTT::base::ChannelElement< ::KDL::JntArray >;
template class RTT::OutputPort< ::KDL::JntArray >;
template class RTT::InputPort< ::KDL::JntArray >;
template class RTT::Property< ::KDL::JntArray >;
template class RTT::Attribute< ::KDL::JntArray >;


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
#if (RTT_VERSION_MAJOR*100+RTT_VERSION_MINOR) >= 206
                            , public MemberFactory
#endif
    {
        JntArrayTypeInfo():TemplateTypeInfo<JntArray, true >("KDL.JntArray")
        {
        }
        
#if (RTT_VERSION_MAJOR*100+RTT_VERSION_MINOR) >= 206
            bool installTypeInfoObject(TypeInfo* ti) {
                // aquire a shared reference to the this object
                boost::shared_ptr< JntArrayTypeInfo > mthis = boost::dynamic_pointer_cast<JntArrayTypeInfo >( this->getSharedPtr() );
                assert(mthis);
                // Allow base to install first
                TemplateTypeInfo<JntArray,true>::installTypeInfoObject(ti);
                // Install the factories for primitive types
                ti->setMemberFactory( mthis );
                // Don't delete us, we're memory-managed.
                return false;
            }
#endif

            /**
             * Specialize to resize \a result given the size of \a source.
             */
            bool composeType( base::DataSourceBase::shared_ptr dssource, base::DataSourceBase::shared_ptr dsresult) const {
                const internal::DataSource<PropertyBag>* pb = dynamic_cast< const internal::DataSource<PropertyBag>* > (dssource.get() );
                if ( !pb )
                    return false;
                internal::AssignableDataSource<JntArray>::shared_ptr ads = boost::dynamic_pointer_cast< internal::AssignableDataSource<JntArray> >( dsresult );
                if ( !ads )
                    return false;

                PropertyBag const& source = pb->rvalue();
                internal::AssignableDataSource<JntArray>::reference_t result = ads->set();

                // take into account sequences:
                base::PropertyBase* sz = source.find("Size");
                if (!sz)
                    sz = source.find("size");
                if (sz)
                {
                    internal::DataSource<int>::shared_ptr sz_ds = internal::DataSource<int>::narrow(sz->getDataSource().get());
                    if (sz_ds)
                        result.resize( sz_ds->get() );
                }
                else
                {
                    // no size found, inform parent of number of elements to come:
                    result.resize( source.size() );
                }
                // recurse into items of this sequence:
                PropertyBag target( source.getType() );
                PropertyBag decomp;
                internal::ReferenceDataSource<JntArray> rds(result);
                rds.ref(); // prevent dealloc.
                // we compose each item in this sequence and then update result with target's result.
                // 1. each child is composed into target (this is a recursive thing)
                // 2. we decompose result one-level deep and 'refresh' it with the composed children of step 1.
                if ( composePropertyBag(source, target) && typeDecomposition( &rds, decomp, false) && ( decomp.getType() == target.getType() ) && refreshProperties(decomp, target, true) ) {
                    assert(result.rows() == source.size());
                    assert(source.size() == target.size());
                    assert(source.size() == decomp.size());
                    ads->updated();
                    Logger::log() <<Logger::Debug<<"Successfuly composed type from "<< source.getType() <<Logger::endl;
                    return true;
                }
                return false;
            }

            /**
             * Use getMember() for decomposition...
             */
            base::DataSourceBase::shared_ptr decomposeType(base::DataSourceBase::shared_ptr source) const
            {
                return base::DataSourceBase::shared_ptr();
            }


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
        RTT::types::Types()->addType( new CArrayTypeInfo<RTT::types::carray< JntArray > >("KDL.cJntArray[]") );
    }
}  
