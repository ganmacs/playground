package typ

import scalaz._
import Scalaz._

object Typer {
  sealed trait TrafficLight
  case object Red extends TrafficLight
  case object Green extends TrafficLight
  case object Yellow extends TrafficLight

  implicit val TrafficLightEqual: Equal[TrafficLight] = Equal.equal(_ == _)
}
