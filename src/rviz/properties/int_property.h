/*
 * Copyright (c) 2012, Willow Garage, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of the Willow Garage, Inc. nor the names of its
 *       contributors may be used to endorse or promote products derived from
 *       this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */
#ifndef INT_PROPERTY_H
#define INT_PROPERTY_H

#include "rviz/macros.h"

#include "rviz/properties/property.h"

namespace rviz
{

/** @brief Property specialized to provide max/min enforcement for integers. */
class RVIZ_DECL IntProperty: public Property
{
Q_OBJECT
public:
  /** @brief Constructor.
   * @param name The name of this property.  Appears in the left column of a PropertyTreeWidget.
   * @param default_value The initial value to store in the property.  Appears in the right column of a PropertyTreeWidget.
   * @param description Text describing the property.  Is shown in the "help" area of a PropertyTreeWithHelp widget.
   * @param parent The parent Property, or NULL if there is no parent at this time.
   * @param changed_slot This should be a Qt slot specification,
   *        generated by Qt's @c SLOT() macro.  It should be a slot on
   *        the @a receiver object, or if @a receiver is not specified,
   *        it should be a slot on the @a parent.
   * @param receiver If receiver is non-NULL, the changed() signal is
   *        connected to the @a changed_slot on the @a receiver object. */
  IntProperty( const QString& name = QString(),
               int default_value = 0,
               const QString& description = QString(),
               Property* parent = 0,
               const char *changed_slot = 0,
               QObject* receiver = 0 );

  /** @brief Set the new value for this property.  Returns true if the
   * new value is different from the old value, false if same.
   *
   * If the new value is different from the old value, this emits
   * aboutToChange() before changing the value and changed() after.
   *
   * Overridden from Property::setValue() to enforce minimum and maximum. */
  virtual bool setValue( const QVariant& new_value );
  
  /** @brief Return the internal property value as an integer.
   *
   * If a non-integer value was stored in this property, this will
   * return 0. */
  virtual int getInt() const { return getValue().toInt(); }

  void setMin( int min );
  int getMin() { return min_; }
  void setMax( int max );
  int getMax() { return max_; }

  /** @brief Overridden to create a QSpinBox with the min and max set
   * and with a signal/slot connection to setInt(), so the Property
   * value updates every time the value changes, not just when
   * "return" is pressed. */
  virtual QWidget* createEditor( QWidget* parent,
                                 const QStyleOptionViewItem& option );

public Q_SLOTS:
  /** @brief Set the value of this property to the given integer.
   *
   * This just calls setValue(), which is where the min/max are enforced. */
  void setInt( int new_value ) { setValue( new_value ); }

private:
  int min_;
  int max_;
};

} // end namespace rviz

#endif // INT_PROPERTY_H
