/*=========================================================================

  Program:   Monteverdi2
  Language:  C++


  Copyright (c) Centre National d'Etudes Spatiales. All rights reserved.
  See Copyright.txt for details.

  Monteverdi2 is distributed under the CeCILL licence version 2. See
  Licence_CeCILL_V2-en.txt or
  http://www.cecill.info/licences/Licence_CeCILL_V2-en.txt for more details.

  This software is distributed WITHOUT ANY WARRANTY; without even
  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
  PURPOSE.  See the above copyright notices for more information.

=========================================================================*/
#include "mvdImageViewRenderer.h"


/*****************************************************************************/
/* INCLUDE SECTION                                                           */

//
// Qt includes (sorted by alphabetic order)
//// Must be included before system/custom includes.
#include <QtOpenGL>

//
// System includes (sorted by alphabetic order)
// necessary for the opengl variables and methods

//
// ITK includes (sorted by alphabetic order)

//
// OTB includes (sorted by alphabetic order)
#include "otbStandardShader.h"

//
// Monteverdi includes (sorted by alphabetic order)
#include "Core/mvdDatasetModel.h"
#include "Core/mvdTypes.h"
#include "Core/mvdVectorImageModel.h"

namespace mvd
{
/*
  TRANSLATOR mvd::ImageViewRenderer

  Necessary for lupdate to be aware of C++ namespaces.

  Context comment for translator.
*/


/*****************************************************************************/
/* CONSTANTS                                                                 */


/*****************************************************************************/
/* STATIC IMPLEMENTATION SECTION                                             */


/*****************************************************************************/
/* CLASS IMPLEMENTATION SECTION                                              */

/*****************************************************************************/
ImageViewRenderer
::ImageViewRenderer( QObject* parent ) :
  AbstractImageViewRenderer( parent ),
  m_GlView( otb::GlView::New() ),
  m_ReferenceImageModel( NULL ),
  m_ReferenceGlImageActor(),
  m_ImageModelActorPairs()
{
  assert( !m_GlView.IsNull() );
}

/*****************************************************************************/
ImageViewRenderer
::~ImageViewRenderer()
{
}

/*****************************************************************************/
bool
ImageViewRenderer
::CheckGLCapabilities() const
{
  qWarning() <<
    ToStdString(
      tr( "Required OpenGL version '%1' with GLSL version '%2'." )
      .arg( otb::GlView::REQUIRED_GL_VERSION )
      .arg( otb::GlView::REQUIRED_GLSL_VERSION )
    ).c_str();

  try
    {
    qWarning() <<
      ToStdString(
        tr( "Runtime OpenGL version '%1' with GLSL version '%2'." )
        .arg( otb::GlView::GLVersion() )
        .arg( otb::GlView::GLSLVersion() )
      ).c_str();
    }
  catch( std::exception& exc )
    {
    qWarning() << ToQString( exc.what() );
    }


  try
    {
    if( otb::GlView::CheckGLCapabilities() )
      return true;


    QMessageBox::critical(
      qobject_cast< QWidget* >( parent() ),
      tr( "Monteverdi2 - Critical error!" ),
      tr( "Current OpenGL version is '%1' supporting GLSL version '%2'.\nRequired OpenGL version is '%3' with Shading-Laguage version '%4'.\nPlease upgrade your graphics driver and hardware for the application to run properly on this platform.\nUsing the application on this platform may lead to unknown behaviour. Would you still like to continue using the application?" )
      .arg( otb::GlView::GLVersion() )
      .arg( otb::GlView::GLSLVersion() )
      .arg( otb::GlView::REQUIRED_GL_VERSION )
      .arg( otb::GlView::REQUIRED_GLSL_VERSION )
    );
    }
  catch( std::exception& exc )
    {
    QMessageBox::critical(
      qobject_cast< QWidget* >( parent() ),
      tr( "Monteverdi2 - Critical error!"),
      ToQString( exc.what() )
    );
    }

  return false; 
}

/*****************************************************************************/
AbstractImageViewRenderer::RenderingContext*
ImageViewRenderer
::NewRenderingContext() const
{
  RenderingContext* context = new ImageViewRenderer::RenderingContext();

#if USE_VIEW_SETTINGS_SIDE_EFFECT
#else
  assert( !m_GlView.IsNull() );

  //
  // Share otb::GlViewRendering settings with manipulator using
  // RenderingContext. Manipulator can then setup otb::ViewSettings
  // directly by side-effect.
  context->m_ViewSettings = m_GlView->GetSettings();
#endif

  return context;
}

/*****************************************************************************/
const AbstractImageModel*
ImageViewRenderer
::GetReferenceImageModel() const
{
  return m_ReferenceImageModel;
}

/*****************************************************************************/
AbstractImageModel*
ImageViewRenderer
::GetReferenceImageModel()
{
  return m_ReferenceImageModel;
}

/*****************************************************************************/
void
ImageViewRenderer
::GetReferenceExtent( PointType& origin, PointType& extent  ) const
{
  assert( !m_ReferenceGlImageActor.IsNull() );

  m_ReferenceGlImageActor->GetExtent(
    origin[ 0 ], origin[ 1 ],
    extent[ 0 ], extent[ 1 ]
  );
}

/*****************************************************************************/
void
ImageViewRenderer
::InitializeGL()
{
  assert( !m_GlView.IsNull() );

  //
  // WARNING: This call to otb::GlView::Initialize() allocates a new
  // otb::ViewSettings() instance. So, the shared pointer between
  // renderer and manipulator may be unshated depending on order of
  // calls.
  //
  m_GlView->Initialize( 0, 0 );
}

/*****************************************************************************/
void
ImageViewRenderer
::ResizeGL( int width, int height )
{
  // qDebug() << this << "::ResizeGL(" << width << "," << height << ")";

  /*
  // Should be done here and not in OTB-Ice render routine.
  glViewport(
    0,
    0,
    static_cast< GLint >( width ),
    static_cast< GLint >( height )
  );
  */

  assert( !m_GlView.IsNull() );

  // qDebug() << m_GlView.GetPointer();

  m_GlView->Resize( width, height );

  /*
  glViewport(
    0, 0,
    static_cast< GLint >( width ), static_cast< GLint >( height )
  );

  glMatrixMode( GL_MODELVIEW );
  glLoadIdentity();

  glMatrixMode( GL_PROJECTION );
  glLoadIdentity();
  glOrtho(
    0, static_cast< GLint >( width ),
    0, static_cast< GLint >( height ),
    0, 1
  );
  */
}

/*****************************************************************************/
void
ImageViewRenderer
::PaintGL( const AbstractImageViewRenderer::RenderingContext* c )
{
  assert( !m_GlView.IsNull() );

  // qDebug() << this << "::PaintGL(" << c << ")";

  // qDebug() << m_GlView.GetPointer();

  /*
  //
  // Get appropriate rendering-context.
  assert( c==dynamic_cast< RenderingContext* >( c ) );
  RenderingContext* context = dynamic_cast< RenderingContext* >( c );
  assert( context!=NULL );

  //
  // Set view settings.
  m_GlView->SetSettings( context->m_ViewSettings );
  */

  //
  // Apply VectorImageModel::Settings to otb::GlImageActor.
  UpdateActors( c );

  //
  // Pre-render scene.
  m_GlView->BeforeRendering();
  {
  //
  // Render scene.
  switch( c->m_RenderMode )
    {
    case RenderingContext::RENDER_MODE_LIGHT:
      m_GlView->LightRender();
      break;

    case RenderingContext::RENDER_MODE_FULL:
      m_GlView->HeavyRender();
      break;
    }
  }
  //
  // Post-render scene.
  m_GlView->AfterRendering();
}

/*****************************************************************************/
bool
ImageViewRenderer
::Pick( const PointType& in,
        PointType& out,
        DefaultImageType::PixelType& pixel )
{
  /*
  qDebug()
    << this << "::Pick("
    << in[ 0 ] << "," << in[ 1 ]
    << ")";
  */

  if( m_ReferenceGlImageActor.IsNull() )
    return false;

  //
  // Compute output/physical point.
  out = m_ReferenceGlImageActor->ViewportToImageTransform( in, true );

  //
  // Read pixel value.
  return m_ReferenceGlImageActor->GetPixelFromViewport( in, pixel );
}

/*****************************************************************************/
bool
ImageViewRenderer
::Transform( PointType& point, const IndexType& index, bool isPhysical ) const
{
  if( m_ReferenceGlImageActor.IsNull() )
    return false;

  point[ 0 ] = static_cast< double >( index[ 0 ] );
  point[ 1 ] = static_cast< double >( index[ 1 ] );

  point = m_ReferenceGlImageActor->ImageToViewportTransform( point, isPhysical );

  return true;
}

/*****************************************************************************/
void
ImageViewRenderer
::UpdateActors( const AbstractImageViewRenderer::RenderingContext* )
{
  UpdateImageActors();
}

/*****************************************************************************/
void
ImageViewRenderer
::UpdateImageActors()
{
  for( ImageModelActorPairMap::const_iterator it(m_ImageModelActorPairs.begin());
       it!=m_ImageModelActorPairs.end();
       ++it )
    {
    assert( it->second.first!=NULL );
    assert( !it->second.second.IsNull() );

    const VectorImageModel::Settings& settings =
      it->second.first->GetSettings();

    //
    // Apply color-setup.
    VectorImageModel::Settings::ChannelVector channels;

    settings.GetSmartChannels( channels );

    it->second.second->SetRedIdx( channels[ RGBW_CHANNEL_RED ] + 1 );
    it->second.second->SetGreenIdx( channels[ RGBW_CHANNEL_GREEN ] + 1 );
    it->second.second->SetBlueIdx( channels[ RGBW_CHANNEL_BLUE ] + 1 );

    //
    // Apply color-dynamics.
    otb::FragmentShader::Pointer fragmentShader( it->second.second->GetShader() );

    assert(
      fragmentShader==otb::DynamicCast< otb::StandardShader >( fragmentShader )
    );

    otb::StandardShader::Pointer shader(
      otb::DynamicCast< otb::StandardShader >( fragmentShader )
    );

    assert( !shader.IsNull() );

    shader->SetMinRed( settings.GetLowIntensity( RGBW_CHANNEL_RED ) );
    shader->SetMaxRed( settings.GetHighIntensity( RGBW_CHANNEL_RED ) );

    shader->SetMinGreen( settings.GetLowIntensity( RGBW_CHANNEL_GREEN ) );
    shader->SetMaxGreen( settings.GetHighIntensity( RGBW_CHANNEL_GREEN ) );

    shader->SetMinBlue( settings.GetLowIntensity( RGBW_CHANNEL_BLUE ) );
    shader->SetMaxBlue( settings.GetHighIntensity( RGBW_CHANNEL_BLUE ) );

    shader->SetGamma( settings.GetGamma() );
    }
}

/*******************************************************************************/
void
ImageViewRenderer
::virtual_ClearScene()
{
  assert( !m_GlView.IsNull() );

  // qDebug() << this << "::virtual_CleraScene()";

  //
  // Remove all actors.
  m_GlView->ClearActors();

  // Forget image-model/actors relationships.
  m_ImageModelActorPairs.clear();

  // Forget reference instances.
  m_ReferenceImageModel = NULL;
  m_ReferenceGlImageActor = otb::GlImageActor::Pointer();
}

/*******************************************************************************/
void
ImageViewRenderer
::virtual_SetImageList( const VectorImageModelList& images )
{
  assert( !m_GlView.IsNull() );

  // qDebug() << this << "::virtual_SetImageList(" << images << ")";

  //
  // Check that references are clear.
  assert( m_ImageModelActorPairs.empty() );
  assert( m_ReferenceImageModel==NULL );
  assert( m_ReferenceGlImageActor.IsNull() );

  //
  // Return if there is no vector-image model.
  if( images.isEmpty() )
    return;

  //
  // Insert new actors corresponding to vector-image model.
  for( VectorImageModelList::const_iterator it( images.begin() );
       it!=images.end();
       ++it )
    {
    assert( *it!=NULL );

    ImageModelActorPair pair(
      *it,
      otb::GlImageActor::New()
    );

    pair.second->Initialize( ToStdString( pair.first->GetFilename() ) );

    DatasetModel* datasetModel = pair.first->GetDatasetModel();

    ActorKey actorKey(
      m_GlView->AddActor(
        pair.second,
        pair.first==NULL
        ? std::string()
        : ToStdString( datasetModel->GetHash() )
      )
    );

    pair.second->SetVisible( true );

    m_ImageModelActorPairs.insert(
      ImageModelActorPairMap::value_type( actorKey, pair )
    );

    qDebug() << "Added image-actor:" << FromStdString( actorKey );
    }

  //
  // Remember first vector image-model as reference image-model.
  m_ReferenceImageModel = images.front();

  //
  // Remember first actor as reference actor.
  otb::GlView::StringVectorType keys( m_GlView->GetRenderingOrder() );
  assert( !keys.empty() );

  otb::GlActor::Pointer glActor( m_GlView->GetActor( keys.front() ) );
  assert( !glActor.IsNull() );

  assert( glActor==otb::DynamicCast< otb::GlImageActor >( glActor ) );

  m_ReferenceGlImageActor = otb::DynamicCast< otb::GlImageActor >( glActor );
  assert( !m_ReferenceGlImageActor.IsNull() );
}

/*****************************************************************************/
/* SLOTS                                                                     */
/*****************************************************************************/

} // end namespace 'mvd'