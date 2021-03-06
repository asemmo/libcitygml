#include "parser/nodetypes.h"
#include "citygml/utils.h"

namespace citygml {

    int NodeType::typeCount = -1;
    std::unordered_map<std::string, NodeType::XMLNode*> NodeType::nodeNameTypeMap;
    std::unordered_map<std::string, NodeType::XMLNode*> NodeType::nodeNameWithPrefixTypeMap;

    bool NodeType::nodesInitialized = false;

    NodeType::XMLNode::XMLNode()
    {
        //
    }

    NodeType::XMLNode::XMLNode(std::string prefix, std::string name ) : m_name(toLower(name)), m_prefix(toLower(prefix))
    {
        m_typeID = NodeType::typeCount++;
    }

    const std::string&NodeType::XMLNode::name() const
    {
        return m_name;
    }

    const std::string&NodeType::XMLNode::prefix() const
    {
        return m_prefix;
    }

    int NodeType::XMLNode::typeID() const
    {
        return m_typeID;
    }

    bool NodeType::XMLNode::operator==(const NodeType::XMLNode& other) const
    {
        return typeID() == other.typeID();
    }

    bool NodeType::XMLNode::operator!=(const NodeType::XMLNode& other) const
    {
        return !(*this == other);
    }

    bool NodeType::XMLNode::valid() const
    {
        return !m_name.empty();
    }

#define INITIALIZE_NODE( prefix, elementname ) \
    NodeType::prefix ## _ ## elementname ## Node = XMLNode( #prefix , #elementname ); \
    NodeType::nodeNameTypeMap[toLower(#elementname)] = &NodeType::prefix ## _ ## elementname ## Node; \
    NodeType::nodeNameWithPrefixTypeMap[toLower(#prefix) + ":" + toLower(#elementname)] = &NodeType::prefix ## _ ## elementname ## Node;

    const NodeType::XMLNode&NodeType::getXMLNodeFor(const std::string& name)
    {
        if(!nodesInitialized) {
            // CORE
            INITIALIZE_NODE( CORE, CityModel )
            INITIALIZE_NODE( CORE, CityObjectMember )
            INITIALIZE_NODE( CORE, CreationDate )
            INITIALIZE_NODE( CORE, TerminationDate )
            INITIALIZE_NODE( CORE, ImplicitGeometry )
            INITIALIZE_NODE( CORE, RelativeGMLGeometry )
            INITIALIZE_NODE( CORE, TransformationMatrix )

            // GRP
            INITIALIZE_NODE( GRP, CityObjectGroup )
            INITIALIZE_NODE( GRP, GroupMember )

            // GEN
            INITIALIZE_NODE( GEN, GenericCityObject )
            INITIALIZE_NODE( GEN, StringAttribute )
            INITIALIZE_NODE( GEN, DoubleAttribute )
            INITIALIZE_NODE( GEN, IntAttribute )
            INITIALIZE_NODE( GEN, DateAttribute )
            INITIALIZE_NODE( GEN, UriAttribute )
            INITIALIZE_NODE( GEN, Value )

            INITIALIZE_NODE( GEN, Lod1Geometry )
            INITIALIZE_NODE( GEN, Lod2Geometry )
            INITIALIZE_NODE( GEN, Lod3Geometry )
            INITIALIZE_NODE( GEN, Lod4Geometry )
            INITIALIZE_NODE( GEN, Lod1TerrainIntersection )
            INITIALIZE_NODE( GEN, Lod2TerrainIntersection )
            INITIALIZE_NODE( GEN, Lod3TerrainIntersection )
            INITIALIZE_NODE( GEN, Lod4TerrainIntersection )

            // TEX
            // INITIALIZE_NODE( GML, TexturedSurface ) // Deprecated

            // GML
            INITIALIZE_NODE( GML, Description )
            INITIALIZE_NODE( GML, Identifier )
            INITIALIZE_NODE( GML, Name )
            INITIALIZE_NODE( GML, DescriptionReference )
            INITIALIZE_NODE( GML, Coordinates )
            INITIALIZE_NODE( GML, Pos )
            INITIALIZE_NODE( GML, BoundedBy )
            INITIALIZE_NODE( GML, Envelope )
            INITIALIZE_NODE( GML, LowerCorner )
            INITIALIZE_NODE( GML, UpperCorner )
            INITIALIZE_NODE( GML, Solid )
            INITIALIZE_NODE( GML, SurfaceMember )
            INITIALIZE_NODE( GML, BaseSurface )
            INITIALIZE_NODE( GML, Patches )
            INITIALIZE_NODE( GML, TrianglePatches )
            INITIALIZE_NODE( GML, SolidMember )
            INITIALIZE_NODE( GML, TriangulatedSurface )
            INITIALIZE_NODE( GML, Triangle )
            INITIALIZE_NODE( GML, Polygon )
            INITIALIZE_NODE( GML, Rectangle )
            INITIALIZE_NODE( GML, PosList )
            INITIALIZE_NODE( GML, OrientableSurface )
            INITIALIZE_NODE( GML, LinearRing )

            INITIALIZE_NODE( BLDG, Lod1Solid )
            INITIALIZE_NODE( BLDG, Lod2Solid )
            INITIALIZE_NODE( BLDG, Lod3Solid )
            INITIALIZE_NODE( BLDG, Lod4Solid )
            INITIALIZE_NODE( BLDG, Lod1Geometry )
            INITIALIZE_NODE( BLDG, Lod2Geometry )
            INITIALIZE_NODE( BLDG, Lod3Geometry )
            INITIALIZE_NODE( BLDG, Lod4Geometry )
            INITIALIZE_NODE( BLDG, Lod1MultiCurve )
            INITIALIZE_NODE( BLDG, Lod2MultiCurve )
            INITIALIZE_NODE( BLDG, Lod3MultiCurve )
            INITIALIZE_NODE( BLDG, Lod4MultiCurve )
            INITIALIZE_NODE( BLDG, Lod1MultiSurface )
            INITIALIZE_NODE( BLDG, Lod2MultiSurface )
            INITIALIZE_NODE( BLDG, Lod3MultiSurface )
            INITIALIZE_NODE( BLDG, Lod4MultiSurface )
            INITIALIZE_NODE( BLDG, Lod1TerrainIntersection )
            INITIALIZE_NODE( BLDG, Lod2TerrainIntersection )
            INITIALIZE_NODE( BLDG, Lod3TerrainIntersection )
            INITIALIZE_NODE( BLDG, Lod4TerrainIntersection )

            INITIALIZE_NODE( GML, MultiPoint )
            INITIALIZE_NODE( GML, MultiCurve )
            INITIALIZE_NODE( GML, MultiSurface )
            INITIALIZE_NODE( GML, MultiSolid )

            INITIALIZE_NODE( GML, CompositeCurve )
            INITIALIZE_NODE( GML, CompositeSurface )
            INITIALIZE_NODE( GML, CompositeSolid )

            INITIALIZE_NODE( GML, ReferencePoint )
            INITIALIZE_NODE( GML, Point )

            INITIALIZE_NODE( GML, Interior )
            INITIALIZE_NODE( GML, Exterior )

            // BLDG
            INITIALIZE_NODE( BLDG, Building )
            INITIALIZE_NODE( BLDG, BuildingPart )
            INITIALIZE_NODE( BLDG, Room )
            INITIALIZE_NODE( BLDG, Door )
            INITIALIZE_NODE( BLDG, Window )
            INITIALIZE_NODE( BLDG, BuildingInstallation )
            INITIALIZE_NODE( BLDG, Address )
            INITIALIZE_NODE( BLDG, MeasuredHeight )
            INITIALIZE_NODE( BLDG, Class )
            INITIALIZE_NODE( BLDG, Type )
            INITIALIZE_NODE( BLDG, Function )
            INITIALIZE_NODE( BLDG, Usage )
            INITIALIZE_NODE( BLDG, YearOfConstruction )
            INITIALIZE_NODE( BLDG, YearOfDemolition )
            INITIALIZE_NODE( BLDG, StoreysAboveGround )
            INITIALIZE_NODE( BLDG, StoreysBelowGround )
            INITIALIZE_NODE( BLDG, StoreyHeightsAboveGround )
            INITIALIZE_NODE( BLDG, StoreyHeightsBelowGround )
            INITIALIZE_NODE( BLDG, BoundedBy )
            INITIALIZE_NODE( BLDG, OuterBuildingInstallation)
            INITIALIZE_NODE( BLDG, InteriorBuildingInstallation)
            INITIALIZE_NODE( BLDG, InteriorRoom)
            INITIALIZE_NODE( BLDG, InteriorFurniture)
            INITIALIZE_NODE( BLDG, RoomInstallation)
            INITIALIZE_NODE( BLDG, Opening)
            INITIALIZE_NODE( BLDG, ConsistsOfBuildingPart )

            // CityFurniture
            INITIALIZE_NODE( FRN, CityFurniture )
            INITIALIZE_NODE( FRN, Lod1Geometry )
            INITIALIZE_NODE( FRN, Lod2Geometry )
            INITIALIZE_NODE( FRN, Lod3Geometry )
            INITIALIZE_NODE( FRN, Lod4Geometry )
            INITIALIZE_NODE( FRN, Lod1TerrainIntersection )
            INITIALIZE_NODE( FRN, Lod2TerrainIntersection )
            INITIALIZE_NODE( FRN, Lod3TerrainIntersection )
            INITIALIZE_NODE( FRN, Lod4TerrainIntersection )
            INITIALIZE_NODE( FRN, Lod1ImplicitRepresentation )
            INITIALIZE_NODE( FRN, Lod2ImplicitRepresentation )
            INITIALIZE_NODE( FRN, Lod3ImplicitRepresentation )
            INITIALIZE_NODE( FRN, Lod4ImplicitRepresentation )

            // BoundarySurfaceType
            INITIALIZE_NODE( BLDG, WallSurface )
            INITIALIZE_NODE( BLDG, RoofSurface )
            INITIALIZE_NODE( BLDG, GroundSurface )
            INITIALIZE_NODE( BLDG, ClosureSurface )
            INITIALIZE_NODE( BLDG, FloorSurface )
            INITIALIZE_NODE( BLDG, InteriorWallSurface )
            INITIALIZE_NODE( BLDG, CeilingSurface )
            INITIALIZE_NODE( BLDG, BuildingFurniture )
            INITIALIZE_NODE( BLDG, RoofType)
            INITIALIZE_NODE( BLDG, ExternalReference)
            INITIALIZE_NODE( BLDG, InformationSystem)
            INITIALIZE_NODE( BLDG, ExternalObject)
            INITIALIZE_NODE( BLDG, Uri)

            INITIALIZE_NODE( BLDG, CityFurniture )

            // ADDRESS
            INITIALIZE_NODE( XAL, XalAddress )
            INITIALIZE_NODE( XAL, Administrativearea )
            INITIALIZE_NODE( XAL, Country )
            INITIALIZE_NODE( XAL, CountryName )
            INITIALIZE_NODE( XAL, Code )
            INITIALIZE_NODE( XAL, Street )
            INITIALIZE_NODE( XAL, PostalCode )
            INITIALIZE_NODE( XAL, City )
            INITIALIZE_NODE( XAL, LocalityName )
            INITIALIZE_NODE( XAL, Thoroughfare )
            INITIALIZE_NODE( XAL, ThoroughfareNumber )
            INITIALIZE_NODE( XAL, ThoroughfareName )
            INITIALIZE_NODE( XAL, Locality )
            INITIALIZE_NODE( XAL, AddressDetails )
            INITIALIZE_NODE( XAL, DependentLocalityName )
            // WTR
            INITIALIZE_NODE( WTR, WaterBody )

            // VEG
            INITIALIZE_NODE( VEG, PlantCover )
            INITIALIZE_NODE( VEG, SolitaryVegetationObject )
            INITIALIZE_NODE( VEG, Species )
            INITIALIZE_NODE( VEG, Lod1ImplicitRepresentation )
            INITIALIZE_NODE( VEG, Lod2ImplicitRepresentation )
            INITIALIZE_NODE( VEG, Lod3ImplicitRepresentation )
            INITIALIZE_NODE( VEG, Lod4ImplicitRepresentation )

            // TRANS
            INITIALIZE_NODE( TRANS, TrafficArea )
            INITIALIZE_NODE( TRANS, AuxiliaryTrafficArea )
            INITIALIZE_NODE( TRANS, Track )
            INITIALIZE_NODE( TRANS, Road )
            INITIALIZE_NODE( TRANS, Railway )
            INITIALIZE_NODE( TRANS, Square )

            // LUSE
            INITIALIZE_NODE( LUSE, LandUse )

            // dem
            INITIALIZE_NODE( LUSE, Lod )
            INITIALIZE_NODE( LUSE, TINRelief )

            // SUB
            INITIALIZE_NODE( SUB, Tunnel )
            INITIALIZE_NODE( SUB, RelativeToTerrain )

            // BRID
            INITIALIZE_NODE( BRID, Bridge )
            INITIALIZE_NODE( BRID, BridgeConstructionElement )
            INITIALIZE_NODE( BRID, BridgeInstallation )
            INITIALIZE_NODE( BRID, BridgePart )

            // APP
            INITIALIZE_NODE( APP, Appearance )
            INITIALIZE_NODE( APP, SimpleTexture )
            INITIALIZE_NODE( APP, ParameterizedTexture )
            INITIALIZE_NODE( APP, GeoreferencedTexture )
            INITIALIZE_NODE( APP, ImageURI )
            INITIALIZE_NODE( APP, TextureMap )
            INITIALIZE_NODE( APP, Target )
            INITIALIZE_NODE( APP, TexCoordList )
            INITIALIZE_NODE( APP, TextureCoordinates )
            INITIALIZE_NODE( APP, TextureType )
            INITIALIZE_NODE( APP, Repeat )
            INITIALIZE_NODE( APP, WrapMode )
            INITIALIZE_NODE( APP, BorderColor )
            INITIALIZE_NODE( APP, PreferWorldFile )

            INITIALIZE_NODE( APP, X3DMaterial )
            INITIALIZE_NODE( APP, Material )
            INITIALIZE_NODE( APP, AppearanceMember )
            INITIALIZE_NODE( APP, SurfaceDataMember )
            INITIALIZE_NODE( APP, Shininess )
            INITIALIZE_NODE( APP, Transparency )
            INITIALIZE_NODE( APP, SpecularColor )
            INITIALIZE_NODE( APP, DiffuseColor )
            INITIALIZE_NODE( APP, EmissiveColor )
            INITIALIZE_NODE( APP, AmbientIntensity )
            INITIALIZE_NODE( APP, IsFront )
            INITIALIZE_NODE( APP, Theme )
            INITIALIZE_NODE( APP, MimeType )

            nodesInitialized = true;
        }

        std::string lowerName = toLower(name);
        {
            auto it = nodeNameWithPrefixTypeMap.find(lowerName);
            if (it != nodeNameWithPrefixTypeMap.end()) {
                return *it->second;
            }
        }

        std::string nodeName = lowerName;

        size_t pos = name.find_first_of( ":" );
        if ( pos != std::string::npos ) {
            nodeName = name.substr(pos);
        }

        auto it = nodeNameTypeMap.find(nodeName);

        if (it == nodeNameTypeMap.end()) {
            return InvalidNode;
        } else {
            return *it->second;
        }
    }

    std::ostream& operator<<(std::ostream& os, const NodeType::XMLNode& o)
    {
        if (!o.valid()) {
            os << "InvalidNode";
        } else {
            if (!o.prefix().empty()) {
                os << o.prefix() << ":";
            }
            os << o.name();
        }

        return os;
    }

    const NodeType::XMLNode NodeType::InvalidNode = XMLNode("", "");

#define DEFINE_NODE( prefix, elementname ) NodeType::XMLNode NodeType::prefix ## _ ## elementname ## Node;

    // CORE
    DEFINE_NODE( CORE, CityModel )
    DEFINE_NODE( CORE, CityObjectMember )
    DEFINE_NODE( CORE, CreationDate )
    DEFINE_NODE( CORE, TerminationDate )
    DEFINE_NODE( CORE, ImplicitGeometry )
    DEFINE_NODE( CORE, RelativeGMLGeometry )
    DEFINE_NODE( CORE, TransformationMatrix )

    // GRP
    DEFINE_NODE( GRP, CityObjectGroup )
    DEFINE_NODE( GRP, GroupMember )

    // GEN
    DEFINE_NODE( GEN, GenericCityObject )
    DEFINE_NODE( GEN, StringAttribute )
    DEFINE_NODE( GEN, DoubleAttribute )
    DEFINE_NODE( GEN, IntAttribute )
    DEFINE_NODE( GEN, DateAttribute )
    DEFINE_NODE( GEN, UriAttribute )
    DEFINE_NODE( GEN, Value )

    DEFINE_NODE( GEN, Lod1Geometry )
    DEFINE_NODE( GEN, Lod2Geometry )
    DEFINE_NODE( GEN, Lod3Geometry )
    DEFINE_NODE( GEN, Lod4Geometry )
    DEFINE_NODE( GEN, Lod1TerrainIntersection )
    DEFINE_NODE( GEN, Lod2TerrainIntersection )
    DEFINE_NODE( GEN, Lod3TerrainIntersection )
    DEFINE_NODE( GEN, Lod4TerrainIntersection )

    // TEX
    // DEFINE_NODE( GML, TexturedSurface ) // Deprecated

    // GML
    DEFINE_NODE( GML, Description )
    DEFINE_NODE( GML, Identifier )
    DEFINE_NODE( GML, Name )
    DEFINE_NODE( GML, DescriptionReference )
    DEFINE_NODE( GML, Coordinates )
    DEFINE_NODE( GML, Pos )
    DEFINE_NODE( GML, BoundedBy )
    DEFINE_NODE( GML, Envelope )
    DEFINE_NODE( GML, LowerCorner )
    DEFINE_NODE( GML, UpperCorner )
    DEFINE_NODE( GML, Solid )
    DEFINE_NODE( GML, SurfaceMember )
    DEFINE_NODE( GML, BaseSurface )
    DEFINE_NODE( GML, Patches )
    DEFINE_NODE( GML, TrianglePatches )
    DEFINE_NODE( GML, SolidMember )
    DEFINE_NODE( GML, TriangulatedSurface )
    DEFINE_NODE( GML, Triangle )
    DEFINE_NODE( GML, Polygon )
    DEFINE_NODE( GML, Rectangle )
    DEFINE_NODE( GML, PosList )
    DEFINE_NODE( GML, OrientableSurface )
    DEFINE_NODE( GML, LinearRing )

    DEFINE_NODE( BLDG, Lod1Solid )
    DEFINE_NODE( BLDG, Lod2Solid )
    DEFINE_NODE( BLDG, Lod3Solid )
    DEFINE_NODE( BLDG, Lod4Solid )
    DEFINE_NODE( BLDG, Lod1Geometry )
    DEFINE_NODE( BLDG, Lod2Geometry )
    DEFINE_NODE( BLDG, Lod3Geometry )
    DEFINE_NODE( BLDG, Lod4Geometry )
    DEFINE_NODE( BLDG, Lod1MultiCurve )
    DEFINE_NODE( BLDG, Lod2MultiCurve )
    DEFINE_NODE( BLDG, Lod3MultiCurve )
    DEFINE_NODE( BLDG, Lod4MultiCurve )
    DEFINE_NODE( BLDG, Lod1MultiSurface )
    DEFINE_NODE( BLDG, Lod2MultiSurface )
    DEFINE_NODE( BLDG, Lod3MultiSurface )
    DEFINE_NODE( BLDG, Lod4MultiSurface )
    DEFINE_NODE( BLDG, Lod1TerrainIntersection )
    DEFINE_NODE( BLDG, Lod2TerrainIntersection )
    DEFINE_NODE( BLDG, Lod3TerrainIntersection )
    DEFINE_NODE( BLDG, Lod4TerrainIntersection )

    DEFINE_NODE( GML, MultiPoint )
    DEFINE_NODE( GML, MultiCurve )
    DEFINE_NODE( GML, MultiSurface )
    DEFINE_NODE( GML, MultiSolid )

    DEFINE_NODE( GML, CompositeCurve )
    DEFINE_NODE( GML, CompositeSurface )
    DEFINE_NODE( GML, CompositeSolid )

    DEFINE_NODE( GML, ReferencePoint )
    DEFINE_NODE( GML, Point )

    DEFINE_NODE( GML, Interior )
    DEFINE_NODE( GML, Exterior )

    // BLDG
    DEFINE_NODE( BLDG, Building )
    DEFINE_NODE( BLDG, BuildingPart )
    DEFINE_NODE( BLDG, Room )
    DEFINE_NODE( BLDG, Door )
    DEFINE_NODE( BLDG, Window )
    DEFINE_NODE( BLDG, BuildingInstallation )
    DEFINE_NODE( BLDG, Address )
    DEFINE_NODE( BLDG, MeasuredHeight )
    DEFINE_NODE( BLDG, Class )
    DEFINE_NODE( BLDG, Type )
    DEFINE_NODE( BLDG, Function )
    DEFINE_NODE( BLDG, Usage )
    DEFINE_NODE( BLDG, YearOfConstruction )
    DEFINE_NODE( BLDG, YearOfDemolition )
    DEFINE_NODE( BLDG, StoreysAboveGround )
    DEFINE_NODE( BLDG, StoreysBelowGround )
    DEFINE_NODE( BLDG, StoreyHeightsAboveGround )
    DEFINE_NODE( BLDG, StoreyHeightsBelowGround )
    DEFINE_NODE( BLDG, BoundedBy )
    DEFINE_NODE( BLDG, OuterBuildingInstallation)
    DEFINE_NODE( BLDG, InteriorBuildingInstallation)
    DEFINE_NODE( BLDG, InteriorRoom)
    DEFINE_NODE( BLDG, InteriorFurniture)
    DEFINE_NODE( BLDG, RoomInstallation)
    DEFINE_NODE( BLDG, Opening)
    DEFINE_NODE( BLDG, ConsistsOfBuildingPart )

    // CityFurniture
    DEFINE_NODE( FRN, CityFurniture )
    DEFINE_NODE( FRN, Lod1Geometry )
    DEFINE_NODE( FRN, Lod2Geometry )
    DEFINE_NODE( FRN, Lod3Geometry )
    DEFINE_NODE( FRN, Lod4Geometry )
    DEFINE_NODE( FRN, Lod1TerrainIntersection )
    DEFINE_NODE( FRN, Lod2TerrainIntersection )
    DEFINE_NODE( FRN, Lod3TerrainIntersection )
    DEFINE_NODE( FRN, Lod4TerrainIntersection )
    DEFINE_NODE( FRN, Lod1ImplicitRepresentation )
    DEFINE_NODE( FRN, Lod2ImplicitRepresentation )
    DEFINE_NODE( FRN, Lod3ImplicitRepresentation )
    DEFINE_NODE( FRN, Lod4ImplicitRepresentation )

    // BoundarySurfaceType
    DEFINE_NODE( BLDG, WallSurface )
    DEFINE_NODE( BLDG, RoofSurface )
    DEFINE_NODE( BLDG, GroundSurface )
    DEFINE_NODE( BLDG, ClosureSurface )
    DEFINE_NODE( BLDG, FloorSurface )
    DEFINE_NODE( BLDG, InteriorWallSurface )
    DEFINE_NODE( BLDG, CeilingSurface )
    DEFINE_NODE( BLDG, BuildingFurniture )
    DEFINE_NODE( BLDG, RoofType)
    DEFINE_NODE( BLDG, ExternalReference)
    DEFINE_NODE( BLDG, InformationSystem)
    DEFINE_NODE( BLDG, ExternalObject)
    DEFINE_NODE( BLDG, Uri)

    DEFINE_NODE( BLDG, CityFurniture )

    // ADDRESS
    DEFINE_NODE( XAL, XalAddress )
    DEFINE_NODE( XAL, Administrativearea )
    DEFINE_NODE( XAL, Country )
    DEFINE_NODE( XAL, CountryName )
    DEFINE_NODE( XAL, Code )
    DEFINE_NODE( XAL, Street )
    DEFINE_NODE( XAL, PostalCode )
    DEFINE_NODE( XAL, City )
    DEFINE_NODE( XAL, LocalityName )
    DEFINE_NODE( XAL, Thoroughfare )
    DEFINE_NODE( XAL, ThoroughfareNumber )
    DEFINE_NODE( XAL, ThoroughfareName )
    DEFINE_NODE( XAL, Locality )
    DEFINE_NODE( XAL, AddressDetails )
    DEFINE_NODE( XAL, DependentLocalityName )
    // WTR
    DEFINE_NODE( WTR, WaterBody )

    // VEG
    DEFINE_NODE( VEG, PlantCover )
    DEFINE_NODE( VEG, SolitaryVegetationObject )
    DEFINE_NODE( VEG, Species )
    DEFINE_NODE( VEG, Lod1ImplicitRepresentation )
    DEFINE_NODE( VEG, Lod2ImplicitRepresentation )
    DEFINE_NODE( VEG, Lod3ImplicitRepresentation )
    DEFINE_NODE( VEG, Lod4ImplicitRepresentation )

    // TRANS
    DEFINE_NODE( TRANS, TrafficArea )
    DEFINE_NODE( TRANS, AuxiliaryTrafficArea )
    DEFINE_NODE( TRANS, Track )
    DEFINE_NODE( TRANS, Road )
    DEFINE_NODE( TRANS, Railway )
    DEFINE_NODE( TRANS, Square )

    // LUSE
    DEFINE_NODE( LUSE, LandUse )

    // dem
    DEFINE_NODE( LUSE, Lod )
    DEFINE_NODE( LUSE, TINRelief )

    // SUB
    DEFINE_NODE( SUB, Tunnel )
    DEFINE_NODE( SUB, RelativeToTerrain )

    // BRID
    DEFINE_NODE( BRID, Bridge )
    DEFINE_NODE( BRID, BridgeConstructionElement )
    DEFINE_NODE( BRID, BridgeInstallation )
    DEFINE_NODE( BRID, BridgePart )

    // APP
    DEFINE_NODE( APP, Appearance )
    DEFINE_NODE( APP, SimpleTexture )
    DEFINE_NODE( APP, ParameterizedTexture )
    DEFINE_NODE( APP, GeoreferencedTexture )
    DEFINE_NODE( APP, ImageURI )
    DEFINE_NODE( APP, TextureMap )
    DEFINE_NODE( APP, Target )
    DEFINE_NODE( APP, TexCoordList )
    DEFINE_NODE( APP, TextureCoordinates )
    DEFINE_NODE( APP, TextureType )
    DEFINE_NODE( APP, Repeat )
    DEFINE_NODE( APP, WrapMode )
    DEFINE_NODE( APP, BorderColor )
    DEFINE_NODE( APP, PreferWorldFile )

    DEFINE_NODE( APP, X3DMaterial )
    DEFINE_NODE( APP, Material )
    DEFINE_NODE( APP, AppearanceMember )
    DEFINE_NODE( APP, SurfaceDataMember )
    DEFINE_NODE( APP, Shininess )
    DEFINE_NODE( APP, Transparency )
    DEFINE_NODE( APP, SpecularColor )
    DEFINE_NODE( APP, DiffuseColor )
    DEFINE_NODE( APP, EmissiveColor )
    DEFINE_NODE( APP, AmbientIntensity )
    DEFINE_NODE( APP, IsFront )
    DEFINE_NODE( APP, Theme )
    DEFINE_NODE( APP, MimeType )

}
