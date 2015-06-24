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

#ifndef __mvdMainWindow_h
#define __mvdMainWindow_h

//
// Configuration include.
//// Included at first position before any other ones.
#include "ConfigureMonteverdi2.h"

#define USE_PIXEL_DESCRIPTION ( ( defined( _DEBUG ) && 0 ) || 0 )


/*****************************************************************************/
/* INCLUDE SECTION                                                           */


#ifndef USE_OTB_APPS
#  define USE_OTB_APPS ( ( defined( _DEBUG ) && 0 ) || 0 )
#endif

//
// Qt includes (sorted by alphabetic order)
//// Must be included before system/custom includes.
#include <QtOpenGL>

//
// System includes (sorted by alphabetic order)

//
// ITK includes (sorted by alphabetic order)

//
// OTB includes (sorted by alphabetic order)

//
// Monteverdi includes (sorted by alphabetic order)
#include "Core/mvdTypes.h"
#include "Core/mvdStackedLayerModel.h"
//
#include "Gui/mvdI18nMainWindow.h"


/*****************************************************************************/
/* PRE-DECLARATION SECTION                                                   */

//
// External class pre-declaration.
namespace
{
}

namespace mvd
{
//
// Internal class pre-declaration.
// Core
class AbstractLayerModel;
// Gui
class FilenameDragAndDropEventFilter;
class ImageViewWidget;
class LayerStackWidget;
class ShaderWidget;
class StatusBarWidget;

namespace Ui
{
class MainWindow;
}

/*****************************************************************************/
/* CLASS DEFINITION SECTION                                                  */

/**
 * \class MainWindow
 *
 * \brief The application main-widow widget.
 */
class Monteverdi2_EXPORT MainWindow
  : public I18nMainWindow
{

  /*-[ QOBJECT SECTION ]-----------------------------------------------------*/

  Q_OBJECT;

  /*-[ PUBLIC SECTION ]------------------------------------------------------*/

//
// Public types.
public:

//
// Public methods.
public:
  /** \brief Constructor. */
  MainWindow( QWidget* Parent =0, Qt::WindowFlags flags =0 );

  /** \brief Destructor. */
  virtual ~MainWindow();

  /**
   */
  bool CheckGLCapabilities() const;

  /*-[ PROTECTED SLOTS SECTION ]---------------------------------------------*/

//
// Public slots.
public slots:

  /**
   */
  inline void ImportImage( const QString & filename );

  /**
   */
  inline void ImportImages( const QStringList & filenames );

  /*-[ SIGNALS SECTION ]-----------------------------------------------------*/

//
// SIGNALS.
signals:

  void UserCoordinatesEditingFinished(const QString&);

  void UserScaleEditingFinished(const QString &);

  void UserZoomIn();

  void UserZoomOut();

  void UserZoomExtent();

  void UserZoomFull();

  void UserZoomLayer();

  /*-[ PROTECTED SECTION ]---------------------------------------------------*/

//
// Protected methods.
protected:

  /**
   */
  void ImportImage( const QString& filename, bool forceCreate );

  using I18nMainWindow::ImportImage;

  //
  // QMainWindow overrides.

  void closeEvent( QCloseEvent* event );

//
// Protected attributes.
protected:

  /*-[ PROTECTED SLOTS SECTION ]---------------------------------------------*/

//
// Protected slots.
protected slots:

  /**
   */
  void OnAboutToChangeModel( const AbstractModel * );

  /**
   */
  void OnModelChanged( AbstractModel * );

  /**
   */
  // void OnAboutToChangeSelectedDatasetModel( const DatasetModel* );

  /**
   */
  // void OnSelectedDatasetModelChanged( DatasetModel* );

  /**
   */
  void OnAboutToChangeSelectedLayerModel( const StackedLayerModel::KeyType & );

  /**
   */
  void OnSelectedLayerModelChanged( const StackedLayerModel::KeyType & );

  /**
   */
  void OnApplicationToLaunchSelected( const QString & appName, const QString & docName );

  /**
   */
  void OnTabCloseRequested( int index );

  /**
   */
  void OnTabCloseRequested();

  /** */
  void OnOTBApplicationOutputImageChanged( const QString & appName,
                                           const QString & outfname);

  /**
   */
  void OnExecutionDone( int status );

  /*-[ PRIVATE SECTION ]-----------------------------------------------------*/

//
// Private types.
private:


//
// Private methods.
private:

  /**
   */
  ImageViewWidget* CreateImageViewWidget( QGLWidget* sharedGlWidget =NULL );

  /**
   */
  ImageViewWidget* CreateQuicklookViewWidget( QGLWidget* sharedGlWidget =NULL );

  /**
   */
  void InitializeDockWidgets();

  /**
   */
  void InitializeCentralWidget();

  /**
   */
  void InitializeRenderToolBar();

  /**
   */
  void InitializeStatusBarWidgets();

  /**
   */
  inline
    const ImageViewWidget* GetQuicklookView() const;
  /**
   */
  inline
    ImageViewWidget* GetQuicklookView();

  /**
   */
  void ConnectImageViews();

  /**
   */
  void ConnectViewMenu();

  /**
   */
  void ConnectReferenceLayerComboBox( StackedLayerModel * );

  /**
   */
  void DisconnectReferenceLayerComboBox( StackedLayerModel * );

  /**
   */
  void SetupReferenceLayerComboBox( StackedLayerModel * );

  /**
   */
  void ConnectStatusBar( AbstractLayerModel * model );

  /**
   */
  void DisconnectStatusBar( const AbstractLayerModel * model );

#if USE_PIXEL_DESCRIPTION

  /**
   */
  void ConnectPixelDescriptionWidget( AbstractLayerModel * model);

  /**
   */
  void DisconnectPixelDescriptionWidget( const AbstractLayerModel * model );

#endif // USE_PIXEL_DESCRIPTION

  //
  // I18nMainWindow overrides.

  virtual void virtual_SetupUI();

  virtual void virtual_ConnectUI();

  virtual void virtual_InitializeUI();

//
// Private attributes.
private:
  /**
   * \brief uic generated.
   */
  Ui::MainWindow* m_UI;

  /**
   * \brief Color dynamicsk-view dock-widget.
   */
  QDockWidget* m_ColorDynamicsDock;

  /**
   * \brief Color setup dock-widget.
   */
  QDockWidget* m_ColorSetupDock;

  /**
   * \brief Database-browser dock-widget.
   */
  // QDockWidget* m_DatabaseBrowserDock;

  /**
   * \brief Dataset-properties dock-widget.
   */
  // QDockWidget* m_DatasetPropertiesDock;

  /**
   * \brief Layer-stack dock-widget.
   */
  QDockWidget * m_LayerStackDock;

  /**
   * \brief Current Pixel Description dock-widget.
   */
#if USE_PIXEL_DESCRIPTION
  QDockWidget* m_PixelDescriptionDock;
#endif // USE_PIXEL_DESCRIPTION

  /**
   * \brief Histogram dock-widget.
   */
  QDockWidget* m_HistogramDock;


#ifdef OTB_USE_QT4
  /**
   *  \brief OTB-applications browser dock-widget.
   */
  QDockWidget* m_OtbApplicationsBrowserDock;
#endif

  /**
   * \brief Image-view page.
   */
  ImageViewWidget* m_ImageView;

  /**
   * \brief Quicklook-view dock.
   */
  QDockWidget* m_QuicklookViewDock;

  /**
   */
  QTabWidget* m_CentralTabWidget;

  /**
   */
  StatusBarWidget* m_StatusBarWidget;

  /**
   */
  ShaderWidget * m_ShaderWidget;

  /**
   */
  FilenameDragAndDropEventFilter* m_FilenameDragAndDropEventFilter;

  /*-[ PRIVATE SLOTS SECTION ]-----------------------------------------------*/

//
// Private slots.
private slots:
  /**
   * \brief Qt auto-connected slot which is called when 'File/Open
   * image' menu action is triggered.
   */
  void on_action_OpenImage_triggered();

  /**
   * \brief Qt auto-connected slot which is called when
   * 'File/Preferences' menu action is trigerred.
   */
  void on_action_Preferences_triggered();

  /**
   * \brief Qt auto-connected slot which is called when zoom-in button
   * is pressed.
   */
  void on_action_ZoomIn_triggered();

  /**
   * \brief Qt auto-connected slot which is called when zoom-out button
   * is pressed.
   */
  void on_action_ZoomOut_triggered();

  /**
   * \brief Qt auto-connected slot which is called when zoom-extent button
   * is pressed.
   */
  void on_action_ZoomExtent_triggered();

  /**
   * \brief Qt auto-connected slot which is called when zoom-full button
   * is pressed.
   */
  void on_action_ZoomFull_triggered();

  /**
   * \brief Qt auto-connected slot which is called when zoom-layer button
   * is pressed.
   */
  void on_action_ZoomLayer_triggered();

  /**
   */
  void OnReferenceLayerCurrentIndexChanged( int );

  /**
   */
  void OnReferenceLayerChanged( size_t );

  /**
   */
  void OnSettingsUpdated();

  /**
   */
  void RefreshReferenceLayerComboBox();

};

} // end namespace 'mvd'

/*****************************************************************************/
/* INLINE SECTION                                                            */

//
// System includes (sorted by alphabetic order)

//
// ITK includes (sorted by alphabetic order)

//
// OTB includes (sorted by alphabetic order)

//
// Monteverdi includes (sorted by alphabetic order)
#include "Gui/mvdImageViewWidget.h"

//
// Some constants.

namespace mvd
{

/*****************************************************************************/
inline
const ImageViewWidget*
MainWindow
::GetQuicklookView() const
{
  return qobject_cast< const ImageViewWidget* >( m_QuicklookViewDock->widget() );
}

/*****************************************************************************/
inline
ImageViewWidget*
MainWindow
::GetQuicklookView()
{
  return qobject_cast< ImageViewWidget* >( m_QuicklookViewDock->widget() );
}

/*****************************************************************************/
void
MainWindow
::ImportImage( const QString & filename )
{
  ImportImage( filename, true );
}

/*****************************************************************************/
void
MainWindow
::ImportImages( const QStringList & filenames )
{
  if( filenames.isEmpty() )
    return;

  for( QStringList::const_iterator it( filenames.constBegin() );
       it!=filenames.end();
       ++it )
    ImportImage( *it );
}

} // end namespace 'mvd'

#endif // __MainWindow_h